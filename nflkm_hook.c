
/*
 * Basic LKM to hook Netfilter hook and then release. 
 * This LKM will drop all UDP packets to port 54.
 */

// Standard headers for LKMs


#include <linux/init.h>    /* Needed for the macros */
#include <linux/module.h>  
#include <linux/kernel.h>  /* We're doing kernel work */
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/tty.h>      /* console_print() interface */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SJM");
MODULE_DESCRIPTION("A simple Linux LKM that prints hello world to the kernel log");



static struct nf_hook_ops *nfho = NULL;

/* Our hook function*/

static unsigned int hfunc(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	struct iphdr *iph;
	struct udphdr *udph;
	if (!skb)
		return NF_ACCEPT;

	iph = ip_hdr(skb);
	if (iph->protocol == IPPROTO_UDP) {
		udph = udp_hdr(skb);
		if (ntohs(udph->dest) == 54) {
            printk(KERN_INFO "Dropped UDP packet to port 54\n");
			return NF_DROP;
		}
	}
	else if (iph->protocol == IPPROTO_TCP) {
		return NF_ACCEPT;
	}
	
	return NF_ACCEPT;
}



/* Initialize the LKM */
int init_module(void)
{
    int err;
    printk(KERN_INFO "Loading Netfilter Hooks.\n");


  /* If we return a non zero value, it means that 
   * init_module failed and the LKM can't be loaded 
   */

    nfho = (struct nf_hook_ops *)kcalloc(1, sizeof(struct nf_hook_ops), GFP_KERNEL);
  
	/* Initialize netfilter hook */
	nfho->hook 	= (nf_hookfn*)hfunc;		/* hook function */
	nfho->hooknum 	= NF_INET_PRE_ROUTING;		/* received packets */
	nfho->pf 	= PF_INET;			/* IPv4 */
	nfho->priority 	= NF_IP_PRI_FIRST;		/* max hook priority */
	
	err = nf_register_net_hook(&init_net, nfho); 
    printk(KERN_INFO "Registered NF Hook %d\n", err);
    return 0;
}


/* Cleanup - undo whatever init_module did */
void cleanup_module(void)
{
    printk(KERN_INFO "Unloading NF Hook and LKM\n");
    nf_unregister_net_hook(&init_net, nfho);
	kfree(nfho);
    printk(KERN_INFO "Unregistered NF Hook\n");
}
