/*----------------------------------------------------------*/
/*                          PROJEKT 1                       */
/*----------------------------------------------------------*/
/*              datum:  15. 11. 2020                        */
/*              autor:  Pavel Marek                         */
/*              login:  xmarek75                            */        
/*              email:  xmarek75@stud.fit.vutbr.cz          */
/*----------------------------------------------------------*/
/*          program na upravu tabulky a zpracovani dat      */
/*----------------------------------------------------------*/

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

int end_of_row(char *pole)
{   
    int k;
    int line_len=strlen(pole);
    for(int i = 0;i <= line_len; i++)
        if (pole[i]=='\n')
            k=i;
return k;
}
int finddelim (int c,char *pole, char delim)//hleda pozici delimiteru
{
    int k;
    int counter = 1;
    int line_len=strlen(pole);
if (c ==1)
    k=0;
else
{
    for (int i=0; i < line_len; i++)
    {
        if (pole[i] == delim)
        {
            counter++;
            if (counter == c)
            {
                k=i;
            }
        }
    }
}
return k;
}
void dcol(int c, char *pole, char delim, int colnum)//odstraní sloupec číslo C.
{
    int line_len = strlen(pole);
    if(c==1)
    {
        int x = finddelim(c, pole, delim);
        int y = finddelim(c+1, pole, delim)+1;
        for(; y<= line_len; y++)
        {
            pole[x]=pole[y];
            x+=1;            
        }
    }
    else if (c==colnum)
    {
        int x = finddelim(c, pole, delim);
        int y = end_of_row(pole);
        for(; y <= line_len;y++)
        {
            pole[x]=pole[y];
            x+=1;
        }
    }
    else
    {
        int x = finddelim(c, pole, delim);
        int y = finddelim(c+1, pole, delim);
        for(; y <= line_len; y++)
        {
            pole[x]=pole[y];
            x+=1;
        }
    }
    
}
void dcols(int n, int m, char *pole, char delim, int colnum)//dcols N M - odstraní sloupce N až M (N <= M). V případě N=M se příkaz chová stejně jako dcol N.
{  
    int line_len = strlen(pole);
    if(n==1 && m!=colnum)
    {
        int x = finddelim(n, pole, delim);
        int y = finddelim(m+1, pole, delim)+1;
        for(; y <= line_len; y++)
        {
            pole[x]=pole[y];
            x+=1;            
        }
    }
    else if(m==colnum)
    {
        int x = finddelim(n, pole, delim);
        int y = end_of_row(pole);
        for(; y <= line_len;y++)
        {
            pole[x]=pole[y];
            x+=1;
        }
    }
    else
    {
    int x = finddelim(n, pole, delim);
    int y = finddelim(m+1, pole, delim);
    for(; y <= line_len; y++)
        {
            pole[x]=pole[y];
            x+=1;
        }
    }
    colnum -=1;
}
void acol(char *pole,char delim){ //přidá prázdný sloupec za poslední sloupec.
   int line_len = strlen(pole);
   for (int i = 0; i < line_len;i++)
    if (pole[i]=='\n'){
        pole[i]=delim;
        pole[i+1]='\n';
        pole[i+2]='\0';
    }


return;
}
void icol(int c,char *pole, char delim)//vloží prázdný sloupec před sloupec daný číslem C.
{
    int line_len = strlen(pole)+1;
    int  x = finddelim(c, pole, delim);
    for (int i=line_len; i>=x; i--)
    {
        pole[i+1]=pole[i];
    }

 pole[x]=delim;

}
int rowcouncter(char *pole)
{
int k=0;
int line_len = strlen(pole);
for(int i=0;i<=line_len;i++)
    if(pole[i] =='\n')
        k++;
return k;
}
void irow(char *pole, char delim, int colnum)//vloží řádek tabulky před řádek R > 0 (insert-row).
{   
 
    int j;
    int line_len = strlen(pole);

    for (int i = line_len; i>=0; i--)
            {
                int x = i+colnum;
                pole[x]=pole[i];
            }
    for (j=0; j <colnum-1; j++)
    {
        pole[j]=delim;
    }
    pole[j]='\n';
}
void arow(int colnum,char delim)//arow - přidá nový řádek tabulky na konec tabulky (append-row).
{
    int i;
    for( i =0 ; i < colnum-1;i++)
    {
        printf("%c",delim);
    }
    printf("\n");
    
}
int nahrad_delimitery(char *pole, char* delimiter)
{
    int line_len = strlen(pole);
    int pocet_delimiteru = strlen(delimiter);
    int n=0; //pocitadlo sloupcu
    for (int i = 0 ; i < line_len;i++){
        for (int j = 0 ; j < pocet_delimiteru;j++){
            if (pole[i]==delimiter[j])
            {
                pole[i]=delimiter[0];
                n++;
            }
    }
    }
   int colnum = n+1;
    return colnum;
}
void drow(char *pole, int colnum)// odstraní řádek číslo R > 0 (delete-row).
{
    int j;
    int line_len=strlen(pole);

    for (int i = line_len ; i>=0; i--)
            {
                int x = i+colnum+1;
                pole[x]=pole[i];
            }
    for (j=0; j <colnum-1; j++)
         pole[j]='\0';

    pole[j+2]='\0';


}
void drows(int n,int m,char *pole,int countrow)//drows N M - odstraní řádky N až M (N <= M). V případě N=M se příkaz chová stejně jako drow N.
{
    int line_len = strlen(pole);
    if (countrow >=n && countrow <=m)
        for(int i=0; i < line_len;i++)
            pole[i] = '\0';
    
}
int table(int colnum, int countrow, char *pole, char *delim,char *argv[],int argc) // rozhoduje kterou funkci spustit
{

    for(int i = 3 ; i < argc ; i++)
    {
        if (strcmp(argv[i], "acol")==0)
            {
                acol(pole,*delim);
                colnum +=1;
            }
        else if (strcmp(argv[i], "icol")==0)
            {   
                int c = atoi(argv[i+1]);
                icol(c, pole, *delim);
                colnum +=1;
            }
        else if(strcmp(argv[i], "irow")==0)
            {
                int r = atoi(argv[i+1]);
                if (r==countrow)
                irow(pole,*delim,colnum);
            }
        else if(strcmp(argv[i], "drow")==0)
            {
                int r = atoi(argv[i+1]);
                if (r==countrow)
                drow(pole,colnum);
                countrow -=1;
            }
        else if(strcmp(argv[i], "drows")==0)
            {   
                int n =atoi(argv[i+1]);
                int m =atoi(argv[i+2]);
                drows(n, m, pole,countrow);
                countrow -= m - n ;
            }
        else if(strcmp(argv[i], "dcol")==0)
            {
                int c = atoi(argv[i+1]);
                dcol(c, pole, *delim, colnum);
                colnum -=1;
            }
        else if(strcmp(argv[i], "dcols")==0)
            {   
                int n =atoi(argv[i+1]);
                int m =atoi(argv[i+2]);
                dcols(n, m, pole, *delim, colnum);
                colnum -= m - n;
            }
    }
        
return colnum;   
}
/*------------▼----------------▼-----------------------------------▼----------------▼------------*/
/*------------▼----------------▼-------------UPRAVA DAT------------▼----------------▼------------*/
/*------------▼----------------▼-----------------------------------▼----------------▼------------*/
void one_col(int c, char *pole,char delim, int colnum)//smaze vsechny bunky krome jedne(c)
{   
    if (c==1)
    {
        for(int i = colnum - 1; i > 0; i--)
            dcol(c+1, pole, delim, colnum);
        dcol(colnum, pole, delim, colnum);
    }
    else if(c==colnum)
    {   
        for(int i = colnum - 1; i > 0; i--)
            dcol(1, pole, delim, colnum);  
    }
    else
    {
        for (int i = c-1 ; i > 0; i--)
            dcol(1, pole, delim, colnum);
        for(int i = colnum - c; i > 0; i--)
            dcol(2, pole, delim, colnum);

        dcol(colnum, pole, delim, colnum);   
    }
}
void cset(int c,char *pole,char delim, int colnum,char *string)//cset C STR - do buňky ve sloupci C bude nastaven řetězec STR.
{   
   if(c > 1 && c < colnum) 
   {
        int string_len=strlen(string);
        int char_num = string_len+1; //pocet znaku ve string
        
        dcol(c,pole,delim, colnum);
        
        int x=finddelim(c,pole,delim);
        int line_len = strlen(pole);

        for(int i = line_len ; i >= x ; i-- )
            pole[i+char_num] = pole[i] ;

        x=finddelim(c,pole,delim);
        for(int j =0; j < string_len ; j++)
        {
            pole[x+1] = string[j];
            x +=1;
        }
   }
   else if(c == 1)
   {
        int string_len=strlen(string);
        int char_num = string_len+1; //pocet znaku ve string
        
        dcol(c,pole,delim, colnum);
        
        int x=finddelim(c,pole,delim);
        int line_len = strlen(pole);
        for(int i = line_len ; i >= x ; i-- )
            pole[i+char_num] = pole[i] ;

        x=finddelim(c,pole,delim);
        for(int j =0; j < string_len ; j++)
        {
            pole[x] = string[j];
            x +=1;
        }
        pole[x] = delim;
   }
   else
   {
        int string_len=strlen(string);
        
        dcol(c,pole,delim, colnum);
        int x = end_of_row(pole);

        pole[x] = delim;
        for(int j=0; j < string_len; j++)
        {
            pole[x+1] = string[j];
            x +=1;
        }
        pole[x+1] ='\n';
        pole[x+2] = '\0';
        
    
   }
}
void copy_1(int n, int m, char *pole, char delim,int colnum)
{
 if(n < m)
 {   
    dcol(m, pole, delim, colnum);
    icol(m, pole, delim);
    int del_n = finddelim(n,pole,delim);
    int del_y = finddelim(n+1,pole,delim);

    int del_m = finddelim(m,pole,delim);
    int del_x = finddelim(m+1,pole,delim); 

    int line_len = strlen(pole);
    for(int i = line_len ; i > del_x ;i-- )
        pole[i+(del_y - del_n)-1] = pole[i];
    
    del_m = finddelim(m,pole,delim);
    int x = del_y - del_n;
    del_n = finddelim(n,pole,delim);
    for(int j = 0; j < x; j++)
    {
        pole[del_m+1] = pole[del_n+1];
        del_m +=1;
        del_n +=1;
    }
 }
else //(m > n)
{
    dcol(m, pole, delim, colnum);
    icol(m, pole, delim);
    int del_n = finddelim(n,pole,delim);
    int del_y = finddelim(n+1,pole,delim);

    int del_m = finddelim(m,pole,delim);
    int del_x = finddelim(m+1,pole,delim); 

    int line_len = strlen(pole);
    for(int i = line_len ; i >= del_x +1;i-- )
        pole[i+(del_y - del_n)-1] = pole[i];
    
    del_m = finddelim(m,pole,delim);
    int x = del_y - del_n;
    del_n += (del_y-del_n-1);
    for(int j = 0; j < x; j++)
    {
        pole[del_m+1] = pole[del_n+1];
        del_m +=1;
        del_n +=1;
    }
 }
}
void copy_2(int n, int m, char *pole, char delim,int colnum) //(m==colnum && n >1 )
{
    char string[colnum*100];
    int x= finddelim(n, pole, delim);
    int z = finddelim(n+1,pole,delim);
    int y = finddelim(m,pole,delim);
    strcpy(string, pole);
    dcol(m,pole,delim,colnum);
    for(;x < z; x++)
    {
        pole[y] = pole[x];
        y += 1;
    }
    pole[y]='\n';
    pole[y+1]='\0';
}
void copy_3(int n, int m, char *pole, char delim,int colnum) //(n==1 && m <colnum)
{
    char string[colnum*100];
    int x = finddelim(n,pole,delim);
    int z = finddelim(n+1,pole,delim);
    int y = finddelim(m,pole,delim);
    strcpy(string, pole);
    dcol(m,pole,delim,colnum);
    int line_len = strlen(pole);
    for(int i = line_len; i >= y;i--)
        pole[i+(z-x+1)] = pole[i];
    x = finddelim(n,pole,delim);
    z = finddelim(n+1,pole,delim);
    y = finddelim(m,pole,delim);
    for(;x<z;x++)
        {
        pole[y+1] = pole[x];
        y +=1;
        }
    
}
void copy_4(int n, int m, char *pole, char delim)//(n==1 && m == colnum)
{
    int y = finddelim(m,pole,delim);
    int x = finddelim(n,pole,delim);
    int z = finddelim(n+1,pole,delim);

    for(;x < z;x++)
    {
        pole[y+1] = pole[x];
        y +=1;
    }
    
    pole[y+1] = '\n';
    pole[y+2] = '\0';
}
void copy_5(int n, int m, char *pole, char delim,int colnum)//(m==1 && n >1)
{
    int line_len = strlen(pole);
    int x = finddelim(n,pole,delim);
    int z = finddelim(n+1,pole,delim);
    char string[colnum*100];
    strcpy(string, pole);
    dcol(m, pole, delim, colnum);
    for(int i = line_len ; i >= 0; i--)
        pole[i+(z-x)]= pole[i];
    int dif = z-x;
    for(int j=0 ; j < dif ;j++)
    {
        pole[j] = string[x+1];
        x += 1;
    }

}
void copy_6(int n, int m, char *pole, char delim,int colnum)//(n==colnum && m==1)
{
    int x = finddelim(m,pole,delim);
    int y = finddelim(n,pole,delim);
    int z = end_of_row(pole);
    char string[100];
    strcpy(string,pole);
    dcol(m, pole, delim, colnum);
    
    int line_len = strlen(pole);
    for(int i = line_len; i >= 0; i--)
        pole[i+(z-y)] = pole[i];
    
    for(;y < z-1;y++ )
    {
        pole[x] = string[y+1];
        x +=1;
    }
    pole[x] = delim;
}
void copy_7(int n, int m, char *pole, char delim,int colnum)//(n==colnum && m > 1 && m < colnum)
{
    int x = finddelim(m,pole,delim);
    int y = finddelim(n,pole,delim);
    int z = end_of_row(pole);
    char string[100*colnum];
    strcpy(string,pole);
    dcol(m, pole, delim, colnum);
    
    int line_len = strlen(pole);
    for(int i = line_len; i >= x; i--)
        pole[i+(z-y)] = pole[i];
    
    for(;y < z-1;y++ )
    {
        pole[x+1] = string[y+1];
        x +=1;
    }
    
}
void copy(int n, int m, char *pole, char delim,int colnum)//copy N M - přepíše obsah buněk ve sloupci M hodnotami ze sloupce N.
{
    if(n==m)
    {

    }
    else if(m==colnum && n >1 )
    {
        copy_2(n, m, pole, delim, colnum);
    }
    else if(n==1 && m <colnum)
    {
        copy_3(n, m, pole, delim, colnum);
    }
    else if(n==1 && m == colnum)
    {
        copy_4(n, m, pole, delim);
    }
    else if (m==1 && n >1 && n <colnum)
    {
        copy_5(n, m, pole, delim, colnum);
    }
    else if(n==colnum && m==1 )
    {
        copy_6(n, m, pole, delim, colnum);
    }
    else if(n==colnum && m > 1 && m < colnum)
    {
        copy_7(n, m, pole, delim, colnum);
    }
    else 
    {  
        copy_1(n, m, pole, delim, colnum);
    }
}
void swap(int n, int m , char *pole, char delim, int colnum)//swap N M - zamění hodnoty buněk ve sloupcích N a M.
{   
    if(n > m)
    {
        int a = n;
        n = m;
        m = a;
    }
    
    else{}

    icol(m,pole,delim);
    colnum +=1;
    copy(n, m, pole, delim, colnum);
    copy(m+1,n,pole,delim,colnum);
    dcol(m+1,pole,delim,colnum); 

}
void string_copy_to_col(int c, char delim, int colnum, char *pole, char *string) //nahraje retezec pole (string) do string do bunky c 
{
    icol(1, string, delim);
    
    int string_len = strlen(string);
    int line_len = strlen(pole);
    for(int i = 0; i <= string_len ; i++)
    {
        pole[line_len-1] = string[i];
        line_len += 1;
    }
    colnum +=1;
    copy(1, c+1, pole, delim, colnum);
    dcol(1 ,pole, delim, colnum);
}
void move(int n, int m,char *pole,char delim, int colnum)
{
    if(n !=m)
    {
    char string[colnum*100];
    strcpy(string, pole);
    
    one_col(n, pole, delim, colnum);

    dcol(n, string, delim, colnum);

    if(n < m)
        m-=1;
    icol(m, string, delim);
    
    string_copy_to_col(m, delim, colnum, pole, string);
    }
    else
    {
    }

}
void tolower_c(int c, char *pole, char delim, int colnum) //tolower C - řetězec ve sloupci C bude převeden na malá písmena.
{   
    char string[100*colnum];
    strcpy(string, pole);
    one_col(c, pole, delim, colnum);
    
    //to lower case-----------------------*/
    int diff = 'b' - 'B';
    for (int i=0; pole[i] !='\0'; i++)
    {
        if(pole[i]>='A' && pole[i] <= 'Z')
            pole[i]+= diff;
    }
    /*------------------------------------*/

    string_copy_to_col(c, delim, colnum, pole, string);
}
void toupper_c(int c, char *pole, char delim, int colnum) //toupper C - řetězec ve sloupci C bude převeden na VELKA písmena.
{   
    char string[100*colnum];
    strcpy(string, pole);
    one_col(c, pole, delim, colnum);
    
    //to upper case-----------------------*/
    int diff = 'b' - 'B';
    for (int i=0; pole[i] !='\0'; i++)
    {
        if(pole[i]>='a' && pole[i] <= 'z')
            pole[i]-= diff;
    }
    /*------------------------------------*/
    string_copy_to_col(c, delim, colnum, pole, string);
}
void int_c(int c, char *pole, char delim, int colnum) // int C - odstraní desetinnou část čísla ve sloupci C.
{
    char string[100*colnum];
    strcpy(string, pole);
    one_col(c, pole, delim, colnum);
    int line_len = strlen(pole);

    /*----------------------podminka---------------------*/
    int not_number = 0 ; // not_number==0 -> retezec obsahuje cisla ,nebo desetinny carka,tecky
    int comma_count = 0; // comma_count != 1 -> neobsahuje desetinnou cast

    for(int i = 0; i < line_len-1 ; i++)
    {
        if((pole[i]>= '0' && pole[i]<= '9') || pole[i]==',' || pole[i]=='.') //podminka- muze obsahovat jenom cisla, carky a tecky
        {
            if(pole[i]==',' || pole[i]=='.') 
                comma_count += 1;
        }
        else //neni to cislo
        {
            not_number += 1;
        }
    }
    /*-----------↓-odstranit desetinnou cast-↓------------*/
    if(not_number==0 && comma_count==1)
    {
        for(int j = 0; j < line_len; j++)
        {
            if(pole[j] == ',' || pole[j] == '.')
            {
                pole[j] = '\n';
                pole[j+1] = '\0';
            }
            else
            {
                
            }
        }
    }
    /*----------------------------------------------------*/

    string_copy_to_col(c, delim, colnum, pole, string);
}
void round_c(int c, char *pole, char delim, int colnum)//round C - ve sloupci C zaokrouhlí číslo na celé číslo.
{   
    char string[100*colnum];
    strcpy(string, pole);
    one_col(c, pole, delim, colnum);
    int line_len = strlen(pole);
for(int i = 0; i < line_len-1 ; i++)
    if(pole[i]==',' || pole[i]=='.')
    {
        /*-----------------↓--pricist 0.5--↓------------------*/
        float f1;
        char* end;
        f1 = strtof(pole,&end);
        f1 += 0.5;
        sprintf(pole, "%f", f1);
        /*----------------------podminka---------------------*/
        int not_number = 0 ; // not_number==0 -> retezec obsahuje cisla ,nebo desetinny carka,tecky
        int comma_count = 0; // comma_count != 1 -> neobsahuje desetinnou cast

        for(int i = 0; i < line_len-1 ; i++)
        {
            if((pole[i]>= '0' && pole[i]<= '9') || pole[i]==',' || pole[i]=='.') //podminka- muze obsahovat jenom cisla, carky a tecky
            {
                if(pole[i]==',' || pole[i]=='.') 
                    comma_count += 1;
            }
            else //neni to cislo
            {
                not_number += 1;
            }
        }
        /*-----------↓-odstranit desetinnou cast-↓------------*/
        if(not_number==0 && comma_count==1)
        {
            for(int j = 0; j < line_len; j++)
            {
                if(pole[j] == ',' || pole[j] == '.')
                {
                    pole[j] = '\n';
                    pole[j+1] = '\0';
                }
                else
                {

                }
            }
        }
        /*----------------------------------------------------*/
    }
        string_copy_to_col(c, delim, colnum, pole, string);

}
void data_p(int colnum, char *pole, char *delim,char *argv[],int argc)//rozhoduje kterou funkci spustit
{   
    for(int i = 3 ; i < argc ; i++)
    {
        if(strcmp(argv[i], "cset")==0)
            {   
                int c =atoi(argv[i+1]);
                char *string;
                string = argv[i+2];
                cset(c, pole, *delim, colnum, string);
                
            }
        else if(strcmp(argv[i], "move")==0)
            {   
                int n =atoi(argv[4]);
                int m =atoi(argv[5]);
                move(n, m, pole, *delim,colnum);
            }
        else if(strcmp(argv[i], "copy")==0)
            {   
                int n =atoi(argv[i+1]);
                int m =atoi(argv[i+2]);
                copy(n, m, pole, *delim,colnum);
            }
        else if(strcmp(argv[i], "swap")==0)
            {   
                int n =atoi(argv[i+1]);
                int m =atoi(argv[i+2]);
                swap(n, m, pole, *delim,colnum);
            }
        else if(strcmp(argv[i], "tolower")==0)
            {   
                int c =atoi(argv[i+1]);
                tolower_c(c, pole, *delim,colnum);
            }
        else if(strcmp(argv[i], "toupper")==0)
            {   
                int c =atoi(argv[i+1]);
                toupper_c(c, pole, *delim,colnum);
            }
        else if(strcmp(argv[i], "int")==0)
            {   
                int c =atoi(argv[i+1]);
                int_c(c, pole, *delim, colnum);
            }
        else if(strcmp(argv[i], "round")==0)
            {   
                int c =atoi(argv[i+1]);
                round_c(c, pole, *delim, colnum);
            }
    }
}
/*  rows N M - procesor bude zpracovávat pouze řádky N až M včetně (N <= M). 
    N=1 znamená zpracování od prvního řádku. Pokud je místo čísla M zadán znak 
    - (pomlčka), ta reprezentuje poslední řádek vstupního souboru. Pokud je pomlčka 
    také místo sloupce N, myslí se tím výběr pouze posledního řádku. Pokud není tento 
    příkaz zadán, uvažuje se implicitně o všech řádcích.    */
void rows(int n, int m,int colnum, int countrow, char *pole, char *delim,char *argv[],int argc)//
{   
    if(n <= countrow && m>=countrow )
        data_p(colnum, pole, delim, argv,argc);   
} 
bool last_row()//vraci true pokud jsem na poslednim radku
{
    int znak = fgetc(stdin);
    if (znak == EOF){
        return true;
    }
    ungetc(znak, stdin);
    return false;
} 
int beginswith(int c, char*string,char *pole,char *delim,int colnum) //beginswith C STR - procesor bude zpracovávat pouze ty řádky, jejichž obsah buňky ve sloupci C začíná řetězcem STR.
{   
    char str[100*colnum];
    strcpy(str,pole);
    int string_len = strlen(string);
    int diff = 0;
    int x = 0;
    one_col(c,str,*delim,colnum);
    for(int i = 0; i < string_len ; i++)
    {
        if(str[i] == string[x])
            x+=1;
        else
        {
        diff = 1;
        break;
        }
    }
return diff;
}   
int contains(int c, char*string,char *pole,char *delim,int colnum)//contains C STR - procesor bude zpracovávat pouze ty řádky, jejichž buňky ve sloupci C obsahují řetězec STR.
{   
    int diff = 0;
    char str[100*colnum];
    strcpy(str,pole);
    one_col(c,str,*delim,colnum);
    char *p;
    p = strstr(str,string); // najde ukazatel na prvni znak nebo NULL

    if(p == NULL)
        diff = 1;

return diff;
}
    /*------------▼----------------▼-----------------------------------▼----------------▼------------*/
    /*------------▼----------------▼----------------MAIN---------------▼----------------▼------------*/
    /*------------▼----------------▼-----------------------------------▼----------------▼------------*/
int main(int argc, char *argv[])
{
        int countrow=0;
        char buffer[1000];
        int colnum;
        char *delim = " ";

        if (argc > 2)
        {
            if (strcmp(argv[1], "-d" )==0)
            {   
                delim = argv[2];
            }
        }

    while (fgets(buffer,10000, stdin) != NULL)
    {
        colnum = nahrad_delimitery(buffer, delim);
        if(rowcouncter(buffer)==1)
        countrow++;

        if (argc > 3)
        {   
            colnum = table(colnum, countrow, buffer, delim, argv,argc);
        
            if(strcmp(argv[3], "rows")==0)
            {   
                int n,m;
                if ((strcmp(argv[4], "-")!=0)&&(strcmp(argv[5], "-")==0))
                {   
                    n =atoi(argv[4]);
                    if (n <= countrow)
                        data_p(colnum, buffer, delim, argv,argc); 
                }
                else if ((strcmp(argv[4], "-")==0)&&(strcmp(argv[5], "-")==0))
                {
                    if(last_row()==true)
                     data_p(colnum, buffer, delim, argv,argc);
                }
                else
                {
                    n =atoi(argv[4]);
                    m =atoi(argv[5]);
                    rows(n, m, colnum, countrow, buffer, delim, argv, argc);
                }

                
            }
            else if(strcmp(argv[3], "beginswith")==0)
            {   
                int c =atoi(argv[4]);
                char *string;
                string = argv[5];
                
                if(beginswith(c, string, buffer, delim, colnum)==0)
                    data_p(colnum, buffer, delim, argv,argc);
            }
            else if(strcmp(argv[3], "contains")==0)
            {   
                int c =atoi(argv[4]);
                char *string;
                string = argv[5];
                if (contains(c, string, buffer, delim, colnum)==0)
                    data_p(colnum, buffer, delim, argv,argc);
            }
            else 
                data_p(colnum, buffer, delim, argv,argc);
        }
    printf("%s",buffer);

    }
    for(int i = 3 ; i < argc ; i++)
    if (strcmp(argv[i], "arow")==0)
        {   
            arow(colnum,*delim);
        }    
return 0;
}