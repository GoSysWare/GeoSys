#include <memory.h>
#include "helper.h"

void str2args(char d, char *str, int len, args_t *args)
{
	int i,j,k;

	memset(args,0,sizeof(args_t));
	j=0;
	k=0;
	for(i=0;i<len;i++){
		if(str[i]==0){
			args->v[j].d[k]=0;
			j++;
			break;
		}else if(str[i]==d){
			args->v[j].d[k]=0;
			k=0;
			j++;
			if(j>=MAXARGCOUNT){
				break;
			}
		}else{
			args->v[j].d[k]=str[i];
			k++;
			if(k>=MAXARGLENGTH){
				break;
			}
		}
	}

	args->c=j;
}

void args2str(char d, args_t *args, char *str, int len)
{
	int i,j,k;

	k=0;
	for(i=0;i<args->c;i++){
		if(k==len){
			break;
		}
		for(j=0;j<MAXARGLENGTH;j++){
			if(args->v[i].d[j]==0){
				str[k]=d;
				k++;
				break;
			}else{
				str[k]=args->v[i].d[j];
				k++;
				if(k==len){
					break;
				}
			}
		}
	}

	str[len-1]=0;
}
