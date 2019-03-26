#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
#include<bits/stdc++.h> 

using namespace std;
map<int,int> keyMap; 
//------------------------------------------------
string encrypt_ceasar(string msg,int key){
	for(int i = 0; i < msg.length(); i++) {
		msg[i]= msg[i] + key;
	}
	return msg;
}
//------------------------------------------------
string encrypt_affine(string msg,int a,int b){ 
 
	string cipher = ""; 
	for (int i = 0; i < msg.length(); i++) { 
		
		if(msg[i]!=' ') 		
			cipher = cipher + (char) ((((a * (msg[i]-'A') ) + b) % 26) + 'A'); 
		else
			cipher += msg[i];	 
	} 
	return cipher; 
} 
//------------------------------------------------
string generate_key_vc(string str, string key){ 
    int x = str.size(); 
    for (int i = 0; ; i++){ 
        if (x == i) 
            i = 0; 
        if (key.size() == str.size()) 
            break; 
        key.push_back(key[i]); 
    } 
    return key; 
} 

string encrypt_vc(string str, string key){
    string cipher_text; 
    for (int i = 0; i < str.size(); i++){ 
        int x = (str[i] + key[i]) %26; 
        x += 'A'; 
        cipher_text.push_back(x); 
    } 
    return cipher_text; 
} 
//------------------------------------------------
void setPermutationOrder(string key) {
    for(int i=0; i < key.length(); i++){ 
        keyMap[key[i]] = i; 
    } 
} 

string encryptMessage(string msg,string key) { 
    int row,col,j; 
    string cipher = ""; 
    col = key.length();  
    row = msg.length()/col;  
    if (msg.length() % col) 
        row += 1; 
    char matrix[row][col]; 
    for (int i=0,k=0; i < row; i++){ 
        for (int j=0; j<col; ) { 
            if(msg[k] == '\0') { 
                matrix[i][j] = '_';   
                j++; 
            } 
            if( isalpha(msg[k]) || msg[k]==' ') {  
                matrix[i][j] = msg[k]; 
                j++; 
            } 
            k++; 
        } 
    } 
  
    for (map<int,int>::iterator ii = keyMap.begin(); ii!=keyMap.end(); ++ii) { 
        j=ii->second; 
        for (int i=0; i<row; i++) { 
            if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_') 
                cipher += matrix[i][j]; 
        } 
    } 
  
    return cipher; 
} 
//------------------------------------------------
// Decryption functions
string decrypt_ceasar(string msg,int key){

	for(int i=0;i<msg.length();i++){
		msg[i]=msg[i]-key;
	}
	return msg;
	
}
//------------------------------------------------
string decrypt_affine(string cipher,int a,int b) 
{ 
	string msg = ""; 
	int a_inv = 0; 
	int flag = 0; 
	for (int i = 0; i < 26; i++) { 
		flag = (a * i) % 26; 
		if (flag == 1)	{ 
			a_inv = i; 
		} 
	} 
	for (int i = 0; i < cipher.length(); i++) 
	{ 
		if(cipher[i]!=' ') 
			msg = msg + (char) (((a_inv * ((cipher[i]+'A' - b)) % 26)) + 'A'); 
		else
			msg += cipher[i]; 
	} 

	return msg; 
} 
//------------------------------------------------
string decrypt_vc(string cipher_text, string key) 
{ 
    string orig_text; 
  
    for (int i = 0 ; i < cipher_text.size(); i++) { 

        int x = (cipher_text[i] - key[i] + 26) %26; 
        x += 'A'; 
        orig_text.push_back(x); 
    } 
    return orig_text; 
} 
//------------------------------------------------

string decryptMessage(string cipher,string key) 
{ 
    int col = key.length(); 
  
    int row = cipher.length()/col; 
    char cipherMat[row][col]; 

    for (int j=0,k=0; j<col; j++) 
        for (int i=0; i<row; i++) 
            cipherMat[i][j] = cipher[k++]; 
  
    int index = 0; 
    for( map<int,int>::iterator ii=keyMap.begin(); ii!=keyMap.end(); ++ii) 
        ii->second = index++; 

    char decCipher[row][col]; 
    map<int,int>::iterator ii=keyMap.begin(); 
    int k = 0; 
    for (int l=0,j; key[l]!='\0'; k++) 
    { 
        j = keyMap[key[l++]]; 
        for (int i=0; i<row; i++) 
        { 
            decCipher[i][k]=cipherMat[i][j]; 
        } 
    } 
    string msg = ""; 
    for (int i=0; i<row; i++) 
    { 
        for(int j=0; j<col; j++) 
        { 
            if(decCipher[i][j] != '_') 
                msg += decCipher[i][j]; 
        } 
    } 
    return msg; 
} 


int main(){
	fstream file;
	char msg[100],ch,ch1;
	char name[10];
	int i,j=0,k,key=0;
	int password,varInput,choice;
	cout<<"Welcome to the Program!"<<endl<<"Please input password:";
	cin>>password;
	if(password==1234){
		cout<<"Welcom!"<<"Input your choice"<<endl;
		label1:
			cout<<"Enter:"<<endl<<"1.Encryption"<<endl<<"2.Decryption "<<endl<<"3.View contents of the file, OR"<<endl<<"Press any other key to exit!"<<endl;
        	cin>>varInput;
			if(varInput==1){
        		if(!file){
        			cout<<"File can't be opened";
				}
				else{

            //Encryption Block:				
		            cout<<"Welcome to Encryption Block"<<endl;
		            //Input data to File:				
		            cout<<"Enter name of file:";
		            cin>>name;
		             strcat(name,".txt");
		            file.open(name,ios::out);
		            cout<<"Enter data to the File:";
		            cin.ignore(); //Ignore ENTER command in buffer
		            cin.getline(msg,100);
		            cout<<"Enter type of encryption:\n1.Ceasar\n2.Affine\n3.Vigenère\n4.Columnar Transposition";
		            cin>>choice;
		            //Choices
		            if(choice==1){
		            	cout<<"Enter key:";cin>>key;
						string cipherText = encrypt_ceasar(msg,key); 
						cout << "Encrypted Message is : " << cipherText<<endl;
						file<<cipherText;
			            file.close();
			            cout<<"Data has been successfully encrypted. Going back to main screen! \n"<<endl;
			            goto label1;
					}
					if(choice==2){
						int key1,key2;
						cout<<"Enter key 1:";cin>>key1;
						cout<<"Enter key 2:";cin>>key2;
						string cipherText = encrypt_affine(msg,key1,key2); 
						cout << "Encrypted Message is : " << cipherText<<endl; 
						file<<cipherText;
			            file.close();
			            cout<<"Data has been successfully encrypted. Going back to main screen! \n"<<endl;
			            goto label1;
					}
					if(choice==3){
						string keyword,vc;
						cout<<"Enter the key:";
						cin.ignore() ;
						getline(cin,keyword);
						vc=generate_key_vc(msg,keyword);
						string cipher_text=encrypt_vc(msg,vc);
						cout<<"Encrypted message:"<<cipher_text;
						file<<cipher_text;
			            file.close();
			            cout<<"Data has been successfully encrypted. Going back to main screen! \n"<<endl;
			            goto label1;
					}
					if(choice==4){
							string key;
							cout<<"Enter the key:";
							cin.ignore() ;
							getline(cin,key);
							setPermutationOrder(key); 
					    	// Calling encryption function 
					    	string cipherText = encryptMessage(msg,key); 
					    	cout << "Encrypted Message: " << cipherText << endl; 
					    	file<<cipherText;
				            file.close();
				            cout<<"Data has been successfully encrypted. Going back to main screen! \n"<<endl;
				            goto label1;
						    	
					}
		            
			}
		}
		else if(varInput==2) {
        	if(!file)  	{
        		cout<<"File can't be opened";
			}
			else{
           //Decryption Block:				
           cout<<"Welcome to DECRYPTION BLOCK"<<endl;
           //Opening the file and putting the cursor in the beginning:				
           cin.ignore();
           cout<<"Enter name of file:";
            cin>>name;
             strcat(name,".txt");
           file.open(name,ios::out|ios::in);
        	string text;
  			getline( file, text);
  			cout<<text;
  			cout<<"Enter type of decryption:\n1.Ceasar\n2.Affine\n3.Vigenère\n4.Columnar Transposition";
  			cin>>choice;
  			if(choice==1){
  				cout<<"Enter key:";cin>>key;
  				string decypt_text= decrypt_ceasar(text,key);
				//Calling Decryption function 
				cout << "Decrypted Message is: " << decypt_text; 
				file.seekg(0,ios::beg);
	            file<<decypt_text;

			  }
  			if(choice==2){
  				int key1,key2;
  				cout<<"Enter key 1:";cin>>key1;
				cout<<"Enter key 2:";cin>>key2;
				string decypt_text= decrypt_affine(text,key1,key2);
				//Calling Decryption function 
				cout << "Decrypted Message is: " << decypt_text; 
				file.seekg(0,ios::beg);
	            file<<decypt_text;
				
			  }
			if(choice==3){
				string keyword,vc;
				cout<<"Enter the key:";
				cin.ignore() ;
				getline(cin,keyword);
				vc=generate_key_vc(msg,keyword);
				string decypt_text=decrypt_vc(text,vc);
				cout<<"Decrypted Message is:"<<decypt_text;
				file.seekg(0,ios::beg);
	            file<<decypt_text;
			}
			if(choice==4){
				string key;
				cout<<"Enter the key:";
				cin.ignore() ;
				getline(cin,key);
				setPermutationOrder(key);    
				string decrypt_text=decryptMessage(text,key);
   				cout << "Decrypted Message: " <<decrypt_text<< endl; 
   				file.seekg(0,ios::beg);
	            file<<decrypt_text;
			}
  			
  			
  			
  			
  			file.close();		
		}
			
		}
		else if(varInput==3)
        {
        	if(!file)
        	{
        		cout<<"File can't be opened";

			}
			else{
				
            //To show contents of the file:
            cout<<"Enter name of file:";
            cin>>name;  strcat(name,".txt");
            file.open(name,ios::in);
            cout<<"Current data in the file:";
            while(1)
                {
                    file.get(ch);
                    if(file.eof())
                    break;
                    cout<<ch;

                }
            file.close();
            cout<<"Going back to main screen! \n"<<endl;

            goto label1;

        	}

        }
        else
        {
            cout<<"Thank You!";

        }
}
else
    {
        cout<<"Invalid password! Program will now terminate...";

    }
    return 0;
}
