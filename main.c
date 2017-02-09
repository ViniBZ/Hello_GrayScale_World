#include <stdio.h>

int main(int argc, char *argv[])
{
    //VERIFYING ARGUMENTS
    if(argc!=2)
    {
        printf("\n\n This script takes 1 argument, the name of the bitmap to be conveted.\n\n");
        //return -1;
    }

    FILE *fo=NULL;
    FILE *fd=NULL;

    int size=0;
    int s=0;
    int offset=54;
    int width=0;
    int w[2]={0,0};
    int wc=0;
    int t=0;

    int pad=0;
    int p=0;
    int ch=0;
    int sum=0;

    //OPENING ORIGIN FILE
    //fo=fopen(argv[1],"rb");
    fo=fopen("c516cb9a87811a493c1da69a64941d3f.bmp","rb");
    if(fo==NULL)
    {
       printf("\n\nCouldn't open the origin file: %s.\n\n",argv[1]);
       return -2;
    }

    //CHECKING ORIGIN FILE SIZE
    fseek(fo,0,SEEK_END);
    size=ftell(fo);
    fseek(fo,0,SEEK_SET);

    if(size<=54)
    {
        printf("\n\nInvalid file.\n\n");
        fclose(fo);
        return -3;
    }

    //PARSING METADATA
    fseek(fo,10,SEEK_SET);
    offset=fgetc(fo);

    fseek(fo,18,SEEK_SET);
    w[0]=fgetc(fo);
    w[1]=fgetc(fo);

    width=w[0]+256*w[1];
    pad=4-(width%4);
    width*=3;

    //CHECKING OFFSET
    if(size<=offset)
    {
        printf("\n\nInvalid file.\n\n");
        fclose(fo);
        return -4;
    }

    //CREATING DESTINY FILE
    fd=fopen("result.bmp","wb");
    if(fd==NULL)
    {
        printf("\n\nCouldn't create the destiny file: result.bmp.\n\n");
        fclose(fo);
        return -5;
    }

    //COPYING METADATA
    fseek(fo,0,SEEK_SET);
    s=0;
    while(s<offset)
    {
        ch=fgetc(fo);
        fputc(ch,fd);
        s++;
    }

    //CONVERSION TO GRAY
    while(s<size)
    {
        if(wc<width)
        {
            ch=fgetc(fo);
            sum+=ch;
            wc++;
            t++;
            if(t==3)
            {
                ch=sum/3;
                sum=0;
                fputc(ch,fd);
                fputc(ch,fd);
                fputc(ch,fd);
                t=0;
            }
        }else{
            p=0;
            while(p<pad)
            {
                ch=fgetc(fo);
                fputc(ch,fd);
                p++;
            }
            wc=0;
        }
        s++;
    }




    printf("\n\nFinished generating destiny file.");
    printf("\n\n");

    fclose(fo);
    fclose(fd);
    return 0;
}
