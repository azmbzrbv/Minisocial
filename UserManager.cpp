#include "Media.h"

void UserManager::UploadPosts(User *user)
{
    std::fstream myfile;
    myfile.open("userpost.txt", std::ios::in);

    if(!myfile.is_open())
    {
        throw std::runtime_error("Posts weren't able to uploaded from userpost.txt file");
    }
    std::string content, line, key, value;
    std::vector<std::string> comments;
    bool iscorrectuser=false;
    
    while(getline(myfile, line))
    {
        std::istringstream iss(line);

         if(getline(iss, key, ':'))
         {
            getline(iss, value);
                if(!value.empty() && value.front()==' ')
                {
                    value=value.substr(1);
                }

            if(key.find("Username")!=std::string::npos)   
            {
                 if(value.find(user->username)!=std::string::npos)
                 {
                    iscorrectuser=true;
                 }
                 else
                 {
                    iscorrectuser=false;
                 }
            } 
            else if(key.find("-Content")!=std::string::npos && iscorrectuser)
            {
                   content=value;
            }
            else if(key.find("-----comment")!=std::string::npos && iscorrectuser)
            {
                comments.push_back(value);
            }
            else if(key.find("postend")!=std::string::npos && iscorrectuser)
            {
                 Post post(user, content, comments);
                 user->posts.push_back(post);   
                 comments.clear();
                 content.clear();
            }
         }

    }

    
   myfile.close();
}

void UserManager::addUser(User *user){
    User** newdata= new User*[usersNum+1];

    for(int i=0; i<usersNum; i++)
    {
        newdata[i]=udata[i];
    }

    newdata[usersNum]=user;

    delete []udata;
    udata=newdata;

    usersNum++; 
}

UserManager::~UserManager(){
 for(int i=0; i<usersNum; i++)
 {
    delete udata[i];
 }

 delete [] udata;
 udata=nullptr;
 usersNum=0;
}




void UserManager::loadFromfile(const std::string& filename)
 {
   std::fstream myfile(filename, std::ios::in);
   if(!myfile.is_open())
   {
    throw std::runtime_error("Couldn't open the file for loadin the data to manager " +filename);
   }

   std::string fileName, fileusername, filejob;
   int fileage;
   bool isAdmin;
   std::string line;
   while(getline(myfile, line))
   {
        std::istringstream iss(line);
        std::string key;

        if(getline(iss, key, ':'))
        {
            std::string value;
            getline(iss, value);
                if(!value.empty() && value[0]==' ')
                {
                    value=value.substr(1);
                }

           if(key.find("Name")!=std::string::npos){//find will return npos if will nof find the name
               fileName = value;
           }else if(key.find("Age")!=std::string::npos){ //consider adding the try catch function whihc is in the plan.txt
               fileage=std::stoi(value);
           }  else if (key.find("Admin") != std::string::npos) {
                isAdmin = (value == "1");
           }else if(key.find("Username")!=std::string::npos){
            fileusername=value;
           }else if (key.find("Occupation") != std::string::npos) {
                filejob = value;
                if(!isAdmin)
                {
                    try
                    {
                        User *user=new User(fileusername, fileName, fileage, filejob, isAdmin);
                        Uploadpassword(user);
                        UploadPosts(user);
                        addUser(user);      
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr <<"Exception has occured! "<< e.what() <<std::endl;
                        throw; // rethrowing it to main
                    }
                    
                   
                   
                }
                else{
                    try
                    {
                        User *user=new Admin(fileusername, fileName, fileage, filejob, isAdmin);
                        Uploadpassword(user);
                        UploadPosts(user);
                        addUser(user);
                    }
                    catch(const std::exception& e)
                    {
                        std::cerr <<"Exception has occured"<< e.what() << std::endl;
                        throw; // rethrowing it to main
                    }        
                   
                  
                }
               
           }

        }
   }

  myfile.close();
 }

  User *UserManager::AssignData(User *user)
  {
         for(int i=0; i<usersNum; i++)
         {
            if(user->username==udata[i]->username)
            {
                return udata[i];
            }
         }

         throw std::runtime_error("User not found in the data array");
  }


  void UserManager::UpdatePostData(const std::string &filename) const
  {
    std::fstream myfile(filename, std::ios::out);
    if(!myfile.is_open())
    {
        throw std::runtime_error("Unable to open the file" +filename);
    }

    for(int i=0; i<usersNum; i++)
    {
        myfile<<"Username: "<<udata[i]->username<<std::endl;
        
        if(udata[i]->posts.size()==0)//problem!!
        {
            myfile<<"-No posts"<<std::endl;
            myfile<<std::endl;
            continue;
        }
        for(int j=0; j<udata[i]->posts.size(); j++)
        {
            myfile<<"-Post: "<<j+1<<std::endl;
            myfile<<"-Content: "<<udata[i]->posts[j].getContent()<<std::endl;
            myfile<<"---Comments: "<<std::endl;
            int commentSize=udata[i]->posts[j].getCommentsSize();
            
            if(commentSize==0)
            {
                myfile<<"----- No comments!"<<std::endl;
            }

            for(int k=0; k<commentSize; k++)
            {
                myfile<<"-----comment "<<k+1<<": "<<udata[i]->posts[j].getCommentContentAt(k)<<std::endl;
            }  

            myfile<<"postend"<<std::endl;
            myfile<<std::endl;
        }

        myfile<<std::endl; 
        myfile<<std::endl;
    }

    myfile.close();

  }


  void UserManager::displayOthersposts()
  {
    bool running=true;
    std::cout<<"Which user's posts do you want to see? (please type username!)"<<std::endl
             <<"Type \"Exit\" if you want to go back!"<<std::endl;
    int index=-1;
    std::string username;

    while(running)
    {
        
        std::getline(std::cin>>std::ws, username);
       
        if(username=="Exit" || username=="exit")
        {
            return;
        }

        for(int i=0; i<usersNum;  i++)
        {
            if(udata[i]->username==username)
            {
                running=false;
                index=i;
                break;
            }
        }
        
        if(index==-1)
        {
            std::cout<<"There is no such username! Please, type again"<<std::endl
                     <<"Type \"Exit\" if you want to go back!"<<std::endl;
        }
        else if(udata[index]->posts.size()==0)
        {
            std::cout<<"There are no posts from this user!Please, type another user!"<<std::endl
                     <<"Type \"Exit\" if you want to go back!"<<std::endl;
            running=true;
        }
    }  

    for(int i=0; i<udata[index]->posts.size(); i++)
    {
       udata[index]->posts[i].viewPost(i);
    }  

    running=true;

    while(running)
    {
        int choice; 
        std::cout<<"Click '1' if you want to add comoment!"<<std::endl
                 <<"Click '2' if you want to exit!"<<std::endl;

        std::cin>>choice;
        if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
        {
            std::cin.clear();// clears the error flags on cin so it can work again
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
            std::cout<<"Invalid command"<<std::endl;
        }
        else if(choice>2 || choice<1)
        {
            std::cout<<"Invalid command!"<<std::endl;

        }
        else if(choice==2)
        {
            running = false;
        }
        else if(choice==1)
        {
            int num;
            while(true)
            {
                std::cout<<"Please type the number of the post you want to comment!"<<std::endl;
                std::cout<<"Write '-1' if you want to go back!"<<std::endl;
                std::cin>>num;
                if(std::cin.fail())// check if non-integer value is typed. std::cin fails when data type doesn't match expected type
                    {
                        std::cin.clear();// clears the error flags on cin so it can work again
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Removes bad input from the stream
                        std::cout<<"Invalid command!"<<std::endl;
                    }
                else if(num==-1)
                {
                    break;
                }    
                else if(num<1 || num>udata[index]->posts.size())    
                {
                    std::cout<<"Invalid command!"<<std::endl;
                }
                else{
                udata[index]->posts[num-1].addComment();

                try
                {    
                  UpdatePostData("userpost.txt");
                }
                catch (const std::exception &e)
                {
                    std::cerr<<"Exception has occured! "<<e.what()<<std::endl;
                    return;
                }

                std::cout<<"Your comment has added successfully!!"<<std::endl;
                break;
                }
            }

        }


        
    }
  }


  void UserManager::listUsers()
  {
    std::cout<<"   "<<std::left<<std::setw(25)<<"Name"<<"Username"<<std::endl;
    for(int i=0; i<usersNum; i++)
    {
        if(udata[i]->isAdmin)
        {
            std::cout<<i+1<<". "<<std::left << std::setw(25)<<udata[i]->name
            <<std::setw(15)<<udata[i]->username<<"Admin"<<std::endl;
        }
        else{
            std::cout<<i+1<<". "<<std::left << std::setw(25)<<udata[i]->name
                    <<udata[i]->username<<std::endl;
        }
                  
    }
  }


  void UserManager::SearchUser()
  {
    while(true)
    {
        std::string searchname;
        int index=-1;
        std::cout<<"Please, type the username of the person!"<<std::endl;
        std::getline(std::cin>>std::ws, searchname);

        for(int i=0; i<usersNum; i++) 
        {
            if(udata[i]->username==searchname)
            {
                index=i;
                break;
            }
        }
        
        if(index==-1)
        {
           std::cout<<"The person with this username doesn't exists!"<<std::endl;
           std::cout<<"Please, type a valid username!"<<std::endl;
        }
        else
        {
            if(udata[index]->isAdmin){
               std::cout<<"  Admin"<<std::endl
                        <<"  Full Name: "<<udata[index]->name<<std::endl
                        <<"  Username: "<<udata[index]->username<<std::endl
                        <<"  Age: "<<udata[index]->age<<std::endl
                        <<"  Occupation: "<<udata[index]->job<<std::endl
                        <<"  Number of posts: "<<udata[index]->posts.size()<<std::endl;   
            } 
            else{
               std::cout<<"  Full Name: "<<udata[index]->name<<std::endl
                        <<"  Username: "<<udata[index]->username<<std::endl
                        <<"  Age: "<<udata[index]->age<<std::endl
                        <<"  Occupation: "<<udata[index]->job<<std::endl    
                        <<"  Number of posts: "<<udata[index]->posts.size()<<std::endl;   
            } 
            return;
         }
        }
    }


void UserManager::UpdateUserData(const std::string &filename) const
{
    std::fstream myfile(filename, std::ios::out);
    if(!myfile.is_open())
    {
         throw std::runtime_error("Unable to open the file" +filename);
    }

    for(int i=0; i<usersNum; i++)
    {
        myfile<<"User "<<i+1<<std::endl
              <<"--Admin: "<<udata[i]->isAdmin<<std::endl
              <<"--Name: "<<udata[i]->name<<std::endl
              <<"--Username: "<<udata[i]->username<<std::endl
              <<"--Age: "<<udata[i]->age<<std::endl
              <<"--Occupation: "<<udata[i]->job<<std::endl;

        myfile<<std::endl;
    }


  myfile.close();
}


void UserManager::removeUser(int index)
{
    if (index < 0 || index >= usersNum) 
    {
        throw std::out_of_range("Index out of range");
    }

    User **newdata=new User*[usersNum-1];

    for(int i=0, j=0; i<usersNum; i++)
      {
        if(i!=index)
        {
          newdata[j]=udata[i];
          j++;
        }
      }

    delete udata[index];// delete user object
    delete [] udata;//delete the old array
    udata=newdata;
    usersNum--;
}

void UserManager::Uploadpassword(User *user)
{
    std::fstream myfile("users.txt", std::ios::in);

    if(!myfile.is_open())
    {
       throw std::runtime_error("users.txt file wasn't able to opened for uploading passwords");
    }
    std::string fileusername, filepassword, line;

    while(getline(myfile, line))
    {
        std::istringstream iss(line);
        
        iss>>fileusername>>filepassword;

        if(user->username==fileusername)
        {
            user->password=filepassword;
        }
    }

    myfile.close();
   
}

void UserManager::UpdataUsersfile(const std::string &filename)const
{
    std::fstream myfile;

    myfile.open(filename, std::ios::out);
    if(!myfile.is_open())
    {
        throw std::runtime_error("Unable to open the file" +filename);
    }
    
    myfile<<std::left<<std::setw(17)<<"Users"<<"Password"<<std::endl;

    for(int i=0; i<usersNum; i++)
    {
      myfile << std::left << std::setw(17) <<udata[i]->username <<udata[i]->password << std::endl;

    }
    myfile.close();   

}

