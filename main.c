#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void generatebillheader(char name[50],char date[30]){
time_t t;
time(&t);
printf("\n\n");
printf("\t AM.PM Sweets");
printf("\n\t ----------------");
printf("\nDate:%s",ctime(&t));
printf("\nInvoice To:%s",name);
printf("\n");
printf("---------------------------------------\n");
printf("\nItems\t\t");
printf("Qty\t");
printf("Price\t");
printf("Total\t\t");
printf("\n---------------------------------------");
printf("\n\n");
}
void generatebillbody(char item[30],int qty,float price){
printf("%s\t\t",item);
printf("%d\t",qty);
printf("%.2f\t",price);
printf("%.2f\t\t",qty*price);
printf("\n");
}

void generatebillfooter(float total){
printf("\n");
float dis=0.1*total;
float nettotal=total-dis;
float service=0.13*nettotal;
float grandtotal=nettotal+service;
printf("\n---------------------------------------");
printf("\nSub Total\t\t\t%.2f",total);
printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
printf("\n\t\t\t\t-------");
printf("\nNet Total\t\t\t%.2f",nettotal);
printf("\nService charge @13%s\t\t%.2f","%",service);
printf("\n---------------------------------------");
printf("\nGrand Total\t\t\t%.2f",grandtotal);
printf("\n---------------------------------------");
}
struct items{
char item[20];
float price;
int qty;
};
struct orders{
char customers[50];
char date[50];
int numofitems;
struct items itm[50];
};
int main(){
float total;

int option,n,i;
struct orders ord;
struct orders order;
char savebill='y',contflag='y';
char name[50],un[50],pw[10];
FILE *fp;
printf("===============================");
printf("\n WELCOME TO AM.PM SWEETS");
printf("\n===============================");
printf("\nPlease Enter:");
printf("\nUsername:");
scanf("%s",&un);
printf("Password:");
scanf("%s",&pw);
if(strcmp(un,"admin")==0){
if(strcmp(pw,"9999")==0){
printf("\nLogged in successfully");
printf("\n===============================");
getch();

while(contflag=='y'){
system("CLS");
float total=0;
int invoicefound=0;
printf("=========AM.PM Sweets=========");
printf("\nPlease select your prefered option\n ");
printf("\n1.Generate Invoice");
printf("\n2.Show all Invoice");
printf("\n3.Search the Invoice");

printf("\n4.Exit");
printf("\n\nYour choice: ");
scanf("%d",&option);
fgetc(stdin); //To consume \n got by scanf so that the below fgets can work

switch(option){
case 1:
system("CLS");
printf("\nPlease enter the name of the customer: ");
fgets(ord.customers,50,stdin);
ord.customers[strlen(ord.customers)-1]=0; //reducing 1 to remove \n
printf("\nPlease enter the number of items: ");
scanf("%d",&n);
ord.numofitems=n;
for(i=0;i<n;i++){
fgetc(stdin);
printf("\n\n");
printf("Please enter the item %d\t: ",i+1);
fgets(ord.itm[i].item,20,stdin);
ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
printf("Please enter the quantity : ");
scanf("%d",&ord.itm[i].qty);
printf("Please enter the unit price: ");
scanf("%f",&ord.itm[i].price);
total+=ord.itm[i].qty*ord.itm[i].price;
}
generatebillheader(ord.customers,ord.date);
for(i=0;i<ord.numofitems;i++){
generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
}

generatebillfooter(total);

printf("\nDo you want to save the invoice[y/n]: ");
scanf("%s",&savebill);
if(savebill=='y'){
fp=fopen("AMPMbill.txt","a+");
fwrite(&ord,sizeof(struct orders),1,fp);
if(fwrite!=0){
printf("\nSucessfully Saved");
}
else{
printf("\nError Saving");
}
}
fclose(fp);
break;

case 2:
system("CLS");
fp=fopen("AMPMbill.txt","r");
printf("\n *******Previous invoices*******");
while(fread(&order,sizeof(struct orders),1,fp)){
float tot=0;
generatebillheader(order.customers,order.date);
for(i=0;i<order.numofitems;i++){
generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
tot+=ord.itm[i].qty*ord.itm[i].price;
}
generatebillfooter(tot);

}
fclose(fp);
break;
case 3:
printf("\nEnter the name of the customer: ");
//fgetc(stdin);
fgets(name,50,stdin);
name[strlen(name)-1]=0;
system("CLS");
fp=fopen("AMPMbill.txt","r");
printf("\n *******Invoice of %s*******",name);
while(fread(&order,sizeof(struct orders),1,fp)){
float tot=0;
if(!strcmp(order.customers,name)){
generatebillheader(order.customers,order.date);
for(i=0;i<order.numofitems;i++){
generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
tot+=ord.itm[i].qty*ord.itm[i].price;
}
generatebillfooter(tot);
invoicefound=1;
}
}
if(!invoicefound){
printf("\nSorry the invoice for %s doesnot exist",name);
}
fclose(fp);
break;
case 4:

printf("\n\t\tbye:)\n\n");
exit(0);
break;

default:
printf("\nSorry invalid option");
break;
}
printf("\nDo you want to perform another operation[y/n]: ");
scanf("%s",&contflag);
}
}
else{
printf("\n\t*Wrong password*");
}
}
else{
printf("\n *Username not available*");
}
return 0;
}