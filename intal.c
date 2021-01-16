#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intal.h"



static char* allocate(int n)
{
	char* temp=(char*)malloc(n+1);
	if(temp!=NULL)
	{
			temp[n]='\0';
			return(temp);
	}
	exit(0);
}

static char* remove_leading_zeroes(char* intal)
{
	int i=0,n=strlen(intal);
	while(i<n && intal[i]=='0')
		i++;
	if(i==n)
	{
		char* result=allocate(1);
		result[0]='0';
		free(intal);
		return(result);
	}
	else
	{
		char* result=allocate(n-i);
		strncpy(result,intal+i,n-i);
		free(intal);
		return(result);
	}
}

void* intal_create(const char* str)
{
	int n=strlen(str);
	char* new=allocate(n);
	int i;
	for(i=0;i<n;i++)
	{
		if(str[i]-'0'>=0 && str[i]-'0' <10)
			new[i]=str[i];
		else
		{
			free(new);
			return(NULL);
		}
	}
	new=remove_leading_zeroes(new);
	return(new);
}

void intal_destroy(void* intal)
{
	free(intal);
}

char* intal2str(void* intal)
{
	if(intal==NULL)
	{
		char* r=allocate(3);
		r[0]='N';
		r[1]='a';
		r[2]='N';
		return(r);
	}
	char* temp=(char*)intal;
	int n=strlen(temp);
	char* a=allocate(n);
	for(int i=0;i<n;i++)
		a[i]=temp[i];
	return(a);
	//return((char*)intal);
}

void* intal_increment(void* intal)
{
    if(intal==NULL)
    	return(NULL);
    char* int1=(char*)intal;
    int n=strlen(int1);
    int i=n-1;
    char* result=allocate(n);
    strncpy(result,int1,n);
    while(i>=0 && result[i]=='9')
    {
    	result[i]='0';
    	i--;
    }
    if(i<0)
    {
    	char* new_result=allocate(n+1);
    	new_result[0]='1';
    	strncpy(new_result+1,result,n);
    	free(result);
    	return(new_result);
    }
    else
    {
    	result[i]=((result[i]-'0')+1)+'0';
    	return(result);
    }
}

void* intal_decrement(void* intal)
{
	if(intal==NULL)
		return(NULL);
	char* int1=(char*)intal;
	int n=strlen(int1);
	char* result=allocate(n);
	strncpy(result, int1, n);

	if(n==1 && result[0]=='0')
		return(result);
	int i=n-1;
	
	while(i>=0 && result[i]=='0')
	{
		result[i]='9';
		i--;
	}
	result[i]=((result[i]-'0')-1)+'0';
	result=remove_leading_zeroes(result);
	return(result);
}


int intal_compare(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return(-2);
	char* int1=(char*)intal1;
	char* int2=(char*)intal2;
	int n=strlen(int1), m=strlen(int2);
	if(n<m)
		return(-1);
	if(n>m)
		return(1);
	int i=0;
	if(n==1 && m==1)
	{
		if(int1[0]>int2[0])
			return(1);
		if(int1[0]<int2[0])
			return(-1);
		return(0);
	}
	while(i<n && int1[i]==int2[i])
		i++;
	if(i==n)
		return(0);
	if(int1[i]>int2[i])
		return(1);
	return(-1);
}

void* intal_add(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return(NULL);
	char* int1, *int2;
	int n,m;
	if(intal_compare(intal1,intal2)==1)
	{
		int1=(char*)intal1;
		int2=(char*)intal2;
		n=strlen(int1);
		m=strlen(int2);
	}
	else
	{
		int1=(char*)intal2;
		int2=(char*)intal1;
		n=strlen(int1);
		m=strlen(int2);
	}
	char* result=allocate(n);

	int i=n-1,j=m-1,k=n-1,sum,carry=0;

	while(j>=0)
	{
		sum=(int1[i--]-'0')+(int2[j--]-'0')+carry;

		carry=0;
		if(sum>9)
		{
			sum=sum%10;
			carry=1;
		}
		result[k--]=sum+'0';
	}
	while(i>=0)
	{
		sum=(int1[i--]-'0')+carry;
		carry=0;
		if(sum>9)
		{
			sum=sum%10;
			carry=1;
		}
		result[k--]=sum+'0';
	}
	if(carry==1)
	{
		char* new=allocate(n+1);
		new[0]='1';
		strncpy(new+1,result,n);
		free(result);
		return(new);
	}
	return(result);
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return(0);
	char* int1, *int2;
	int n,m;
	if(intal_compare(intal1,intal2)==1)
	{
		int1=(char*)intal1;
		int2=(char*)intal2;
		n=strlen(int1);
		m=strlen(int2);
	}
	else
	{
		int1=(char*)intal2;
		int2=(char*)intal1;
		n=strlen(int1);
		m=strlen(int2);
	}

	//printf("%s %s\n",int1, int2 );
	char* result=allocate(n);
	int diff, borrow=0,i=n-1,j=m-1,k=n-1;
	while(j>=0)
	{
		diff=(int1[i--]-'0')-(int2[j--]-'0')-borrow;
		borrow=0;
		if(diff<0)
		{
			diff+=10;
			borrow=1;
			result[k--]=diff+'0';
		}
		else
		{
			result[k--]=diff+'0';
		}
	}
	while(i>=0)
	{
		diff=(int1[i--]-'0')-borrow;
		borrow=0;
		if(diff<0)
		{
			diff+=10;
			borrow=1;
			result[k--]=diff+'0';
		}
		else
		{
			result[k--]=diff+'0';
		}
	}
	result=remove_leading_zeroes(result);
	return(result);
}

static char* add_leading_zeroes(char* a, int m)
{	
	int n=strlen(a);
	char* new=allocate(n+m);
	for(int i=0;i<m;i++)
		new[i]='0';
	strncpy(new+m,a,n);
	return(new);
}

static void split(char* a,char* a1,char* a2,int m)
{
	strncpy(a1,a,m);
	strncpy(a2,a+m,m);
}

static char* add_trailing_zeroes(char* a, int m)
{
	int n=strlen(a);
	char* new=allocate(n+m);
	strncpy(new,a,n);
	for(int i=0;i<m;i++)
		new[i+n]='0';
	return(new);
}


static char* compute_karatsuba(char* p1, char* p2, char* p3, int n)
{
	char* term1=add_trailing_zeroes(p1,n);
	//printf("t1: %s\n",term1 );
	char* term2=intal_add(p1,p2);
	//printf("%s %s\n",term2,p3 );
	char* term3=intal_diff(p3,term2);
	//printf("t2: %s\n",term3 );
	//printf("t3: %s\n",p2 );
	free(term2);
	term2=add_trailing_zeroes(term3,n/2);
	free(term3);
	term3=intal_add(term1, term2);
	free(term1);
	free(term2);
	term1=intal_add(term3,p2);
	free(term3);
	free(p1);
	free(p2);
	free(p3);
	
	term2=remove_leading_zeroes(term1);
	return(term2);
}

void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return(NULL);
	char* int1, *int2,*a,*b;
	int n,m;
	if(intal_compare(intal1,intal2)==1)
	{
		int1=(char*)intal1;
		int2=(char*)intal2;
		n=strlen(int1);
		m=strlen(int2);
	}
	else
	{
		int1=(char*)intal2;
		int2=(char*)intal1;
		n=strlen(int1);
		m=strlen(int2);
	}

	if(n==1 && m==1)
	{
		int op1=(int1[0]-'0');
		int op2=(int2[0]-'0');
		int mul=op1*op2;
		if(mul>9)
		{
			char* result=allocate(2);
			result[0]=mul/10+'0';
			result[1]=mul%10+'0';
			return(result);
		}
		char* result=allocate(1);
		result[0]=mul+'0';
		return(result);
	}
	if(n%2!=0)
	{
		n++;
		a=add_leading_zeroes(int1,1);
	}
	else
	{
		a=allocate(n);
		strncpy(a, int1,n);
	}
	if(n!=m)
	{
		b=add_leading_zeroes(int2,n-m);
	}
	else
	{
		b=allocate(n);
		strncpy(b,int2,n);
	}
	char* a1,*a2,*a3,*b1,*b2,*b3,*p1,*p2,*p3;
	m=n/2;
	a1=allocate(m);
	a2=allocate(m);
	b1=allocate(m);
	b2=allocate(m);

	split(a,a1,a2,m);
	split(b,b1,b2,m);

	a3=(char*)intal_add(a1,a2);
	b3=(char*)intal_add(b1,b2);

	//printf("params: %s %s %s %s %s %s\n",a1,a2,b1,b2,a3,b3);

	p1=intal_multiply(a1,b1);
	p2=intal_multiply(a2,b2);
	p3=intal_multiply(a3,b3);
	//printf("p's %s %s %s\n",p1,p2,p3 );

	free(a1);
	a1=NULL;
	free(a2);
	a2=NULL;
	free(a3);
	a3=NULL;
	free(b1);
	b1=NULL;
	free(b2);
	b2=NULL;
	free(b3);
	b3=NULL;
	free(a);
	free(b);

	return(compute_karatsuba(p1,p2,p3,n));
}

void* intal_divide(void* intal1, void* intal2)
{
	if(intal1==NULL||intal2==NULL)
		return(NULL);
	if(intal_compare(intal2,"0")==0)
		return(NULL);
	char* quotient;

	if(intal_compare(intal1,intal2)==-1)
	{
		quotient=intal_create("0");
		return(quotient);
	}
	if(intal_compare(intal1,intal2)==0)
	{
		quotient=intal_create("1");
		return(quotient);
	}
	char* dividend=(char*)intal1,*divisor=(char*)intal2;
	int n=strlen(dividend),m=strlen(divisor),l;
	int i=m-1,q=0,k=0;
	char* temp=allocate(m);
	char* p;
	strncpy(temp,dividend,m);
	quotient=allocate(n);
	memset(quotient,'\0',n);
	while(i<n)
	{
		q=0;
		while(intal_compare(temp,divisor)!=-1)
		{
			temp=intal_diff(temp,divisor);
			q++;
		}
		quotient[k++]=q+'0';
		
		p=temp;
		l=strlen(p);
		
		if(l==1 && p[0]=='0')
		{
			temp=allocate(1);
			temp[0]=dividend[++i];
		}

		else
		{
			temp=allocate(l+1);
			temp[l]=dividend[++i];
			strncpy(temp,p,l);
		}
		free(p);
	}
	p=quotient;
	l=strlen(quotient);
	quotient=allocate(l);
	strncpy(quotient,p,l);
	free(p);
	return(remove_leading_zeroes(quotient));
}


void* intal_pow(void* intal1, void* intal2)
{
	if(intal_compare(intal1,"0")==0)
	{
		char* result=intal_create("0");
		return(result);
	}
	if(intal_compare(intal2,"0")==0)
	{
		char* result=intal_create("1");
		return(result);
	}

	char* div=intal_divide(intal2,"2");
	char* p=intal_pow(intal1,div);
	free(div);
	char* result=intal_multiply(p,p);
	free(p);
	char* int2=(char*)intal2;
	if((int2[strlen(int2)-1]-'0')%2!=0)
	{
		p=intal_multiply(result,intal1);
		free(result);
		return(p);
	}
	return(result);
}




