//'Hello world' netfilter hooks example
//For any packet, we drop it, and log fact to /var/log/messages

#undef _KERNEL_

#include <linux/kernel.h> //required for any kernel modules 
#include <linux/module.h>
#include <linux/netfilter.h> 
#include <linux/netfilter_ipv4.h>

#include <linux/module.h> 	//This is a kernel module.
#include <linux/kernel.h> 	//This is a kernel module.
#include <linux/proc_fs.h> 	//Since we are using proc file system.
#include<linux/sched.h>		//For scheduling.
#include <asm/uaccess.h>	//copy_to_user(), copy_from_user().
#include <linux/slab.h>		//for kmalloc() and kfree()

#include <linux/skbuff.h>  
#include <linux/ip.h>         // for IP header

#include <linux/string.h>
#include <linux/ctype.h>

#define _KERNEL_

// a macro that defines the maximum number of messages;
// that is, the maximum number of IP addresses to filter
#define MAX_MSG 50

//initialize to unblock
bool block = false;

//incoming 
int in_index = 0; //current index for incoming traffic to block. (in_index < MAX_MSG)
char *inList[MAX_MSG]; //array to hold incomming ip addresses to block.

//outgoing 
int out_index = 0; //current index for outgoing traffic to block. (out_index < MAX_MSG)
char *outList[MAX_MSG]; //array to hold outgoing ip addresses to block.


//for incoming traffic 
static struct nf_hook_ops nfhoIN; //struct holding set of hook function options

//for outgoing traffic
static struct nf_hook_ops nfhoOUT; 

//two proc files, one for incoming, and the other one for outgoing.

struct sk_buff *sock_buff;
struct iphdr *ip_header;

char *msg1;
int len1,temp1;

char *msg2;
int len2,temp2;

//This hook function is registered on NF_IP_LOCAL_IN
unsigned int hook_funcIN(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
	
	if(block){
		printk(KERN_INFO "incoming packet dropped\n");
		return NF_DROP;
	} //end if
		
	else if(in_index > 0){

		unsigned int src_ip;
		char source[16];

		sock_buff = skb;		
		// grab network header using accessor
		ip_header = (struct iphdr *) skb_network_header(sock_buff);
		// get the source address
		src_ip = (unsigned int) ip_header -> saddr;
	
		// convert the source IP addresses to character buffers
		snprintf(source, 16, "%pI4", &src_ip);
		
		int i;
		for(i = 0; i < in_index; i++){
			if(strstr(inList[i],source) != NULL){
				printk(KERN_INFO "incoming packet from source addr: %s dropped", source);
				return NF_DROP;
			}	
		}
			
		
		printk(KERN_INFO "incoming packet from source addr: %s accepted", source);
		
		return NF_ACCEPT;	
			
	}

	else {
		printk(KERN_INFO "No incoming traffic to block\n");
		
		return NF_ACCEPT;
	}
}

//This hook function is registered on NF_IP_LOCAL_OUT
unsigned int hook_funcOUT(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {

	if(block){
		printk(KERN_INFO "outgoing packet dropped\n");
		return NF_DROP;
	} 
		
	else if(out_index > 0){

		unsigned int dest_ip;
		
		char dest[16];

		sock_buff = skb;		
		// grad network header using accessor
		ip_header = (struct iphdr *) skb_network_header(sock_buff);
		
		// get the destination address
		dest_ip = (unsigned int) ip_header -> daddr;

		// convert the destination IP addresses to character buffers
		snprintf(dest, 16, "%pI4", &dest_ip);
	
		int i = 0;
		for(i = 0; i < out_index; i++){
			if(strstr(outList[i],dest) != NULL){
				printk(KERN_INFO "outgoing packet to dest addr: %s dropped", dest);
				return NF_DROP;
			}
		}
		
		printk(KERN_INFO "outgoing packet to dest addr: %s accepted", dest);
		return NF_ACCEPT;	
	}

	else {
		printk(KERN_INFO "No outgoing traffic to block.\n");
		
		return NF_ACCEPT;
	}

}

//global int variable of length and tmp.
//len: the number of bytes in msg. (proc entry)
//temp: the number of bytes to be read. Will be set back to len everytime after each read finishes.
int len0,temp0;

//String buffer in the kernel space
//msg = char[10];
char *msg0;

//transfer the data from user space to kernel space 
ssize_t write_proc0(struct file *filp,const char *buf,size_t count,loff_t *offp)
{

	//copy the data from the buffer to msg (in the proc entry).
	copy_from_user(msg0,buf,count);

	//Update len and temp for msg.
	len0=count;
	temp0=len0;

	if(count > 0){
		block = !block;
	}

	//return the number of bytes copied.
	return count;
}


//String buffer in the kernel space
//msg = char[10];


ssize_t write_proc1(struct file *filp,const char *buf,size_t count,loff_t *offp)
{

	//copy the data from the buffer to msg (in the proc entry).
	copy_from_user(msg1,buf,count);
	strim(msg1);

	//Update len and temp for msg.
	len1=count;
	temp1=len1;
	
	//truncate msg1
	msg1[count] = '\0';
	//printk(KERN_INFO "msg1 length = %d\n",strlen(msg1));

	if(count > 0){
	//in_index means the next index to write.
		if(in_index >= MAX_MSG){
		
			printk(KERN_INFO "Cannot add more incoming addresses to block");
		}else{
			
		   //copy the address to inList[in_index]
		   inList[in_index] = kmalloc(count*sizeof(char),GFP_KERNEL);
		   
		   //error checking 
		   if(inList[in_index] == NULL){
			printk(KERN_ERR "Error allocating space for inList");
		   }else{
			
                        strcpy(inList[in_index],msg1); //strcpy(char *dest, const char *src)
			//printk(KERN_INFO "New address: %s\n",inList[in_index]);

			in_index += 1; //update the index 
      			//printk(KERN_INFO "New index: %d\n",in_index);
			
			
		   }	

		}
	}

	//return the number of bytes copied.
	return count;
}

ssize_t write_proc2(struct file *filp,const char *buf,size_t count,loff_t *offp)
{

	//copy the data from the buffer to msg (in the proc entry).
	copy_from_user(msg2,buf,count);
	strim(msg2);

	//Update len and temp for msg.
	len2=count;
	temp2=len2;
	
	//truncate msg2
	msg2[count] = '\0';
	//printk(KERN_INFO "msg2 length = %d\n",strlen(msg2));

	if(count > 0){
	//in_index means the next index to write.
		if(out_index >= MAX_MSG){
		
			printk(KERN_INFO "Cannot add more outgoing addresses to block");
		}else{
			
		   //copy the address to inList[in_index]
		   outList[out_index] = kmalloc(count*sizeof(char),GFP_KERNEL);
		   
		   //error checking 
		   if(outList[out_index] == NULL){
			printk(KERN_ERR "Error allocating space for outList");
		   }else{
			
                        strcpy(outList[out_index],msg2); //strcpy(char *dest, const char *src)
			//printk(KERN_INFO "New address: %s\n",outList[out_index]);

			out_index += 1; //update the index 
      			//printk(KERN_INFO "New index: %d\n",out_index);	
		   }	

		}
	}
	//return the number of bytes copied.
	return count;
}



struct file_operations proc_fops0 = {

	//Those are both callback functions
	write: write_proc0,
};

struct file_operations proc_fops1 = {

	//Those are both callback functions
	write: write_proc1,
};

struct file_operations proc_fops2 = {

	//Those are both callback functions
	write: write_proc2,
};

void create_new_proc_entry(void) 
{

	//Here we pass the file_operations struct toe create the proc entry.
	//NULL: means it's proc/hello 
	proc_create("blockAll",0666,NULL,&proc_fops0);

	//GFP_KERNEL: most reliable, will sleep or swap if out of memory.
	//here we need to allocate more space to entry the message.
	msg0=kmalloc(50*sizeof(char),GFP_KERNEL);

	//For entering incoming address to block
	proc_create("incoming",0666,NULL,&proc_fops1);

	//GFP_KERNEL: most reliable, will sleep or swap if out of memory.
	msg1=kmalloc(50*sizeof(char),GFP_KERNEL);
	
	//For entering outgoing address to block
	proc_create("outgoing",0666,NULL,&proc_fops2);

	//GFP_KERNEL: most reliable, will sleep or swap if out of memory.
	msg2=kmalloc(50*sizeof(char),GFP_KERNEL);
}



//Called when module loaded using "insmod"
int init_module(){

	//setup nf_hook_ops:
	//struct for incoming traffic
	nfhoIN.hook = hook_funcIN; //function to call when conditions below met
	nfhoIN.hooknum = NF_INET_LOCAL_IN;
	nfhoIN.pf = PF_INET;  //IPV4 packets. (ignore IPV6)
	nfhoIN.priority = NF_IP_PRI_FIRST; //set to highest priority over all other hook functions
	nf_register_hook(&nfhoIN); //register hook

	//struct for outgoing traffic
	nfhoOUT.hook = hook_funcOUT;
	nfhoOUT.hooknum = NF_INET_LOCAL_OUT;
	nfhoOUT.pf = PF_INET; //IPV4 packets. (ignore IPV6)
	nfhoOUT.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&nfhoOUT); //register hook


	//Create two proc_entries: one for blockAll and the other one for monitoring.
	create_new_proc_entry();
	printk(KERN_INFO "MAX_MSG = %d\n", MAX_MSG);

	return 0;
}

//Called when module unloaded using "rmmod"
void cleanup_module(){
	
	nf_unregister_hook(&nfhoIN); //cleanup -- unregister hook.
	nf_unregister_hook(&nfhoOUT); 

	//remove blockAll
	remove_proc_entry("blockAll",NULL);
 	kfree(msg0); //free the dynamically allocated memory.

	//remove incoming
	remove_proc_entry("incoming",NULL);
 	kfree(msg1); //free the dynamically allocated memory.

	//remove outgoing
	remove_proc_entry("outgoing",NULL);
 	kfree(msg2); //free the dynamically allocated memory.
	
	int i;	
	for(i = 0; i < in_index; i++){
		kfree(inList[i]);
	}
	
	int j;
	for(j = 0; j < out_index; j++){
		kfree(outList[i]);
	}
}

MODULE_AUTHOR("Xingnan Xia");
MODULE_LICENSE("GPL");   //General Public License