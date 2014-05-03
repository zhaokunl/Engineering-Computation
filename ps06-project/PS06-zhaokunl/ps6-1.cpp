#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveTailControlCode(char str[])
{
    int i,lng;
    lng=strlen(str);
    for(i=lng-1; i>=0; i--)
    {
        if(isprint(str[i])==0)
        {
            str[i]=0;
        }
        else
        {
            break;
        }
    }
}

int main(void)
{

    char key[256];
    printf("Enter File Name>");
    fgets(key, 256 , stdin);
    key[strlen(key)-1]='\0';
    
    FILE*fp;
    fp=fopen(key,"r");

    char fm[256];
    printf("Enter Keyword>");
    fgets(fm,255,stdin);
    fm[strlen(fm)-1]='\0';
    int i,j;
    int word=0;
    int digits=0;//Users/zhaokunli/Documents/shakira.txt
    
    if(fp!=NULL)
    {
        char str[256];
        int lnum;
        lnum=1;
        
        while(fgets(str,255,fp)!=NULL)
        {
            RemoveTailControlCode(str);
            char check[256];
            RemoveTailControlCode(check);
            for(i=0; i<strlen(fm); i++)
            {
                if(fm[i]>64 && str[i]<91)
                {
                    check[i]=fm[i]+32;
                }
                else if(fm[i]>96 && str[i]<123)
                {
                    check[i]=fm[i]-32;
                }
            }
            int state=0;
            for(i=1; i<256-strlen(fm); i++)
            {
                  if(str[i]==fm[0] || str[i]==check[0])
                   {
                       for(j=0;j<strlen(fm);j++)
                          {
                                if(str[i+j]==fm[j] || str[i+j]==check[j])
                                  {
                                    digits++;
                                  }
                          }
                       if(digits==strlen(fm))
                       {
                           word++;
                           state=1;
                       }
                       else
                       {
                           digits=0;
                       }
                   }
             }
            if(state==1) printf("%5d: %s\n", lnum,str);
            lnum++;
        }
        printf("Appeared %d times.\n", word);
    }
    else
    {
        printf("Cannot open a file.\n");
    }
    if(fp!=NULL)
    {
        fclose(fp);
    }
    return 0;
}