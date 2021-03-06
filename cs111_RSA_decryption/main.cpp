#include <iostream>
#include<vector>
#include <math.h>
#include <fstream>

#include <sstream>
using namespace std;


void decryption(vector<int>& encrypted, vector<char> &decrypted, int d, int n);
template<typename Item_type>
void vector_print(vector<Item_type> &encrypted);
void driver_decyption();

template<typename Item_type>
void loadFromFile(vector<Item_type> &data);
void SaveToFile( string filename,const vector<char> Data, ofstream &myfile);
int simplifyMod(int root, int exponent, int modValue);


int main()
{


    system("clear");
    driver_decyption();
    return 0;
}
void SaveToFile(string filename, const vector<char> Data, ofstream &myfile)
{
    myfile.open(filename.c_str());
    if(myfile.is_open())
       cout<<"open"<<endl;
        for(size_t i=0;i<Data.size();i++)
         {
            myfile<<Data[i];
            myfile<<" ";
         }

    myfile.close();
}
template<typename Item_type>
void loadFromFile(vector<Item_type> &data)
{
     ifstream myfile;
    //cout<<filename<<endl;
    myfile.open("input.txt");
    Item_type temp;
    if(myfile.is_open())
    {
      while (myfile>>temp)
         data.push_back(temp);
     myfile.close();
    }
    else
    {
        cout << "Unable to open file\n";
    }
   // cout<<"this is what i got:"<<endl;
   //vector_print(data);

}

void decryption(vector<int>& encrypted,vector<char>& decrypted,int d,int n)
{
    //+63
    int size=encrypted.size()-1;
   long long int hold1,hold2,hold_result;
    char value;
    double c;
    for(int i=0;i<size;i++)
    {
        c=encrypted[i];
        cout<<"c= "<<c<<", hold= ";
        hold1=simplifyMod(c, d, n);
        cout<<hold1<<",hold result= ";
       hold_result=(hold1%77);
       cout<<hold_result<<", value= ";
       value=(char)(hold_result+63);
       cout<<value<<endl;
       decrypted.push_back(value);
    }

}

void driver_decyption()
{
      ofstream myfile;
       int d=37;//
      int n=77;
       string s;
       string filename_input;
       string filename_output="output.txt";
       filename_input="a.txt";
       vector<char> message;
       vector<int> encryption;
       loadFromFile(encryption);
       decryption(encryption,message,d,n);
       SaveToFile(filename_output,message,myfile);



}
template<typename Item_type>
void vector_print(vector<Item_type>& encrypted)
{
    int size= encrypted.size()-1;
    for(int i=0;i<size;i++)
        cout<<encrypted[i]<<" ";
    cout<<endl;
}

int simplifyMod(int root, int exponent, int modValue)
{
    if(exponent > 1)
    {
        if(root < modValue)
        {
            if(exponent % 2 == 0)
            {
                return simplifyMod(pow(root, 2), exponent/2, modValue);
            }
            else if(exponent % 2 == 1)
            {
                return(simplifyMod(pow(root, 2), exponent/2, modValue)*simplifyMod(root, 1, modValue));
            }
        }
        else if(root >= modValue)
        {
            return simplifyMod(root%modValue, exponent, modValue);
        }
    }
    return root%modValue;
}
