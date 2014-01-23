#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cmath>

#define sqr(x) ((x)*(x))
using namespace std;

extern void errorf(string);
extern void load_net(string);
extern void save_net(string);
extern void make();
extern double scalar(vector<double>,vector<double>);
extern vector<double> dec(vector<double>,vector<double>);
extern void set_in_image(string);
extern bool set_educate(bool,string);
extern void teach();
extern char getcom();
vector< vector< vector<double> > >w; 
vector< vector< double > > val;
vector< pair< vector<double>, vector<double> > > t;
double E_need;
    
double nu = 10;
double c = 0.1;
int isize = 30;
int show_it = 1000;
double k_plus = 1.000001;
double k_minus = 0.2;
int max_it =  1500000;

void setup_consts()
{
	cout<<"Speed of teaching? (def 0.1)\n";
	cin>>nu;
}

double f(double x)
{
//    return (exp(x)-exp(-x))/(exp(x)+exp(-x));
//    return 1.0/(1+exp(-x*c));
	return x/(c+abs(x));
}
double f_p(double x)
{
//    return 4/(sqr(exp(x)+exp(-x)));
//    return -x*(1-x);
	return c/sqr(abs(x)+c);
}


void calc()
{
    for(int i=1;i<val.size();i++)
    {
	for(int j=0;j<val[i-1].size();j++)
	{
	    val[i-1][j] = f(val[i-1][j]);
	}
	for(int j=0;j<val[i].size();j++)
	{
	    val[i][j] = scalar(w[i][j], val[i-1]); 
	}
    }
}

void set_in()
{
    cout<<"Input IN vector ("<<val[0].size()<<")\n";
    for(int i=0;i<val[0].size();i++)
    {
	cin>>val[0][i];
    }
}
void print_out()
{
    cout<<"OUT vector ("<<val.back().size()<<")\n";
    for(int i=0;i<val.back().size();i++)
    {
	cout<<val.back()[i]<<"\n";
    }
    cout<<"That's all\n";
}
void print_help()
{
    	cout<<"h - help\n";
    	cout<<"q - exit\n";
    	cout<<"l - load network form file\n";
    	cout<<"c - calc(vector)\n";
    	cout<<"r - reconize image (calc for image)\n";
    	cout<<"m - make a new network\n";
    	cout<<"t - teach the network\n";
    	cout<<"e - educate from file\n";
	cout<<"x - set up consts\n";
}

int main()
{
    char c;
    cout<<"Hi!\n";
    cout<<"I am a neuron network. To get more information, type 'h'.\n";
    while(c = getcom())
    {
	if(c=='q')
	{
	    break;
	}
	if(c=='h')
	{
	    print_help();
	}
	if(c=='l')
	{
	    string file;
	    cout<<"Neuron net file name?\n";
	    cin>>file;
	    load_net(file);
	}
	if(c=='s')
	{
	    string file;
	    cout<<"File to save?\n";
	    cin>>file;
	    save_net(file);
	}
	if(c=='c')
	{
	    set_in();
	    calc();
	    print_out();
	}
	if(c=='r')
	{
	    string p;
	    cout<<"Image?:\n";
	    cin>>p;
	    set_in_image(p);
	    calc();
	    print_out();
	}
	if(c=='t')
	{
	    set_educate(true,"");
	    teach();
	}
	if(c=='e')
	{
	    string file;
	    cout<<"Education file:\n";
	    cin>>file;
	    set_educate(false,file);
	    teach();
	}
	if(c=='m')
	{
	    make();
	}
	if(c=='x')
	{
		setup_consts();
	}
	getchar();
    }
    cout<<"Bye!\n";
}
