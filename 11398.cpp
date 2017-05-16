#include <iostream>
#include <string>
using namespace std;

std::string string_replace(std::string str, const std::string &s1, const std::string &s2){
	using std::string;
	string ans,tmp;
	
	int pos;
	ans = str;
	pos = str.find(s1,0);
	while(pos >= 0){
		ans = ans.replace(pos,s1.length(),s2);
		pos = str.find(s1,pos+s1.length());
	}
	
	cout << str << endl;
	return ans;
}
std::string string_change_word(std::string str){
	using std::string;
	string ans;
	int i,j,Firstvowel;
	for(i=0;i<str.length();i=j){
		Firstvowel = 0;
		j= i;
		if(!isalpha(str[j])){
			ans.append(str,j,1);
			j++;
		}else{
			for(j=i; isalpha(str[j]) && j< str.length();j++){
				if(i==j){
					if(str[j]=='a' || str[j]=='e' || str[j]=='i' || str[j]=='o' || str[j]=='u' || str[j]=='A' || str[j]=='E' || str[j]=='I' || str[j]=='O' || str[j]=='U'){
						Firstvowel = 1;	
					} 
				}
			}
			if(Firstvowel){
				ans = ans.append(str,i,j-i);
				ans = ans.append("ay");
			}else if(!Firstvowel){
				ans = ans.append(str,i+1,j-i-1);
				ans = ans.append(str,i,1);
				ans = ans.append("ay");
			}	
		}
	}
	return ans;
}

int main(){
    using std::cout;
    using std::endl;
    using std::cin;
    using std::string;

    string str, s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    while(getline(cin, str)){
        str = string_replace(str, s1, s2);
        str = string_change_word(str);
        cout <<  str  <<endl;
    }

    return 0;
}
