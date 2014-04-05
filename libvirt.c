#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,value=-1,choice,num_domains;
    int *active_domains;
    char name[50];
    virConnectPtr connptr;
    virDomainPtr vdpptr;

    connptr = virConnectOpen("xen:///");

    if (connptr == NULL) {
        fprintf(stderr, "Error opening connection to XEN:/// \n");
        return 1;
    }
    else
    {
        num_domains=virConnectNumOfDomains(connptr);
	active_domains=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(connptr, active_domains, num_domains);

        while(1)
        {
            
            printf("1.Start\n2.Suspend\n3.Resume\n4.stop\n5.exit\n ");
	    printf("\n Enter your choice\n");
            scanf("%d",&choice);

	    if(choice<5)
	    {
              printf("\n Please Insert the Active Domian name ");
              scanf("%s",&name);
  	    }
            
	    vdpptr=virDomainLookupByName(connptr,name);
        
            switch(choice)
            {
                case 1:/* Start */
			value=virDomainCreate(vdpptr);
                       if(value==0)
                           printf("Success");
                       else
                           printf("Failed");
                       break;
                case 2:/* Suspend */
			value=virDomainSuspend(vdpptr);
                       if(value==0)
                           printf("Success");
                       else
                           printf("Failed");
                       break;
                case 3:/* Resume */
			value=virDomainResume(vdpptr);
                        if(value==0)
                            printf("Success");
                        else
                            printf("Failed");
                        break;

                case 4: /* stop */
			value=virDomainShutdown(vdpptr);
                        if(value==0)
                            printf("Success");
                        else
                            printf("Failed");
                        break;
                case 5:exit(0);
		default: exit(0);
            }
        }
        virConnectClose(connptr);
    }
}

