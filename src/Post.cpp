#include "Media.h"

void Post::viewPost(int index)
{
    std::cout<<index+1<<". "<<content<<std::endl;
    std::cout<<"Comments:"<<std::endl;
    if(comments.size()==0)
    {
        std::cout<<"     "<<"No comments"<<std::endl;
    }
    
    for(int i=0; i<comments.size(); i++)
    {
        std::cout<<"     "<<i+1<<". "<<comments[i]<<std::endl;
    }
}


void Post::createPost(User *user)
{
   
    std::cout<<"Please write the content of the new post!"<<std::endl;
    std::getline(std::cin>>std::ws, content);
    author=user;
}

std::string Post::getContent()
{
    return content;
}

std::string Post::getCommentContentAt(int index)
{
    return comments[index];
}

int Post::getCommentsSize()
{
    return comments.size();
}

void Post::addComment()
{
    std::string newcomment;
    std::cout<<"Please, type your comment!"<<std::endl;
    std::getline(std::cin>>std::ws, newcomment);

    comments.push_back(newcomment);

}