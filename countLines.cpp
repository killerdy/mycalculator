#include<iostream>
#include<fstream>
#include<string>
#include<filesystem>
#include<vector>
#include<set>
std::set<std::string> se={
    "src","include"
};
std::vector<int> flag={0};
void check(const std::string &str){
    std::cout<<str.substr(str.rfind('/')+1)<<std::endl;
    if(se.count(str.substr(str.rfind('/')+1)))
    flag.push_back(flag.back()+1);
    else 
    flag.push_back(flag.back());
}
int file_count(const std::string &filename){
    if(flag.back()==0)
    return 0;
    std::ifstream file(filename);
    if(filename.substr(filename.size()-4)!=".cpp"&&filename.substr(filename.size()-2)!=".h")
    return 0;
    // if(!check(filename))
    // return 0;
    if(!file.is_open()){
        std::cout<<"open error";
        return 0;
    }
    std::string line;
    int ans=0;
    while(std::getline(file,line))
    ans++;
    return ans;
}
int dir_count(const std::string &dir){
    int sum=0;
    check(dir);
    for(const auto &entry:std::filesystem::directory_iterator(dir))
    {
        if(entry.is_regular_file())
        sum+=file_count(entry.path().string());
        else {
            sum+=dir_count(entry.path().string());
        }
    }
    flag.pop_back();
    return sum;
}
int main(int argc,char **argv){

    std::string str=argv[1];
    std::cout<<dir_count(str)<<std::endl;
    
    return 0;
}