#include<bits/stdc++.h>
#include<string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;

//extern char ** environ;

void redirec(char *command[])
{
	int pid,fd;
	pid=fork();

	if(pid==0)
	{
		fd=open(command[1],O_TRUNC|O_WRONLY|O_CREAT,0644);
		dup2(fd,1);
		close(fd);
		char *argv1[1000];
		char *p=command[0];
		for(int i=0;i<1000;i++)
		{
			argv1[i]=strsep(&p," ");
			if(argv1[i]==NULL)
				break;
			if(strlen(argv1[i])==0)
				break;
		}
		int i=execvp(argv1[0],argv1);
		if(i<0)
			cout<<"errror in execution";
		exit(0);

	}
	else if(pid<0)
		cout<<"errror in fork creation";
	else
	{
		// close(fd);
		wait(NULL);

		
	}
}


void appendrun(char *command[])
{
	int pid,fd;
	pid=fork();

	if(pid==0)
	{
		fd=open(command[1],O_APPEND|O_WRONLY|O_CREAT,0644);
		dup2(fd,1);
		close(fd);
		char *argv1[1000];
		char *p=command[0];
		for(int i=0;i<1000;i++)
		{
			argv1[i]=strsep(&p," ");
			if(argv1[i]==NULL)
				break;
			if(strlen(argv1[i])==0)
				break;
		}
		int i=execvp(argv1[0],argv1);
		if(i<0)
			cout<<"errror in execution";
		exit(0);

	}
	else if(pid<0)
		cout<<"errror in fork creation";
	else
	{
		// close(fd);
		wait(NULL);

		
	}
}


void piperun(char *command[],int flag)
{
        // cout<<"in piperun"<<endl;
        // for(int i=0;command[i]!=NULL;i++)
        //     cout<<command[i]<<endl;
	if(flag==1)
	{
        int fd[2];
        int j=0,pid,prev=0,fds;
        while(command[j]!=NULL)
        {
            // cout<<"start"<<command[j]<<endl;
            if(pipe(fd)<0)
            {
                cout<<"Pipe could not be intialised\n";
                return;
            }
            pid=fork();
            if(pid==0)
            {
                if(j!=0)
                {
                    dup2(prev,0);
                    // dup2(fd[0],0);
                    
                }
           		
                if(command[j+1]!=NULL)
                    dup2(fd[1],1);
                else if (command[j+1]==NULL)
                {
                	
                	char *argv2[1000];
                	char *p=command[j];
                	for(int i=0;i<1000;i++)
                	{
                		argv2[i]=strsep(&p,">");
                		if(argv2[i]==NULL)
                			break;
                		if(strlen(argv2[i])==0)
                			i--;
                	}
                	// cout<<"argv2[o]"<<argv2[0]<<endl;
                	// cout<<"argv2[1]"<<argv2[1]<<endl;
                	command[j]=argv2[0];
                	command[j+1]=NULL;
                	fds=open(argv2[1],O_TRUNC|O_WRONLY|O_CREAT,0644);
					dup2(fds,1);
					close(fds);

                }
                close(fd[0]);
                close(fd[1]);
                char *p=command[j];
                char *argv1[1000];
                for(int i=0;i<1000;i++)
                {
                    argv1[i]=strsep(&p," ");
                    if(argv1[i]==NULL)
                        break;
                    if(strlen(argv1[i])==0)
                        i--;
                }
                int e=execvp(argv1[0],argv1);

                // cout<<"end"<<command[j]<<endl;

            }
            else if(pid<0)
                cout<<"could not fork\n";
            else
            {

                
                wait(NULL);
                //close(prev);
                prev=fd[0];
                close(fd[1]);
                
                j++;
            }
            

        }
    }

    else if(flag==2)
	{
        int fd[2];
        int j=0,pid,prev=0,fds;
        while(command[j]!=NULL)
        {
            // cout<<"start"<<command[j]<<endl;
            if(pipe(fd)<0)
            {
                cout<<"Pipe could not be intialised\n";
                return;
            }
            pid=fork();
            if(pid==0)
            {
                if(j!=0)
                {
                    dup2(prev,0);
                    // dup2(fd[0],0);
                    
                }
           		
                if(command[j+1]!=NULL)
                    dup2(fd[1],1);
                else if (command[j+1]==NULL)
                {
                	
                	char *argv2[1000];
                	char *p=command[j];
                	for(int i=0;i<1000;i++)
                	{
                		argv2[i]=strsep(&p,">");
                		if(argv2[i]==NULL)
                			break;
                		if(strlen(argv2[i])==0)
                			i--;
                	}
                	// cout<<"argv2[o]"<<argv2[0]<<endl;
                	// cout<<"argv2[1]"<<argv2[1]<<endl;
                	command[j]=argv2[0];
                	command[j+1]=NULL;
                	fds=open(argv2[1],O_APPEND|O_WRONLY|O_CREAT,0644);
					dup2(fds,1);
					close(fds);

                }
                close(fd[0]);
                close(fd[1]);
                char *p=command[j];
                char *argv1[1000];
                for(int i=0;i<1000;i++)
                {
                    argv1[i]=strsep(&p," ");
                    if(argv1[i]==NULL)
                        break;
                    if(strlen(argv1[i])==0)
                        i--;
                }
                int e=execvp(argv1[0],argv1);

                // cout<<"end"<<command[j]<<endl;

            }
            else if(pid<0)
                cout<<"could not fork\n";
            else
            {

                
                wait(NULL);
                //close(prev);
                prev=fd[0];
                close(fd[1]);
                
                j++;
            }
            

        }
    }

    else
    {
    	int fd[2];
        int j=0,pid,prev=0;
        while(command[j]!=NULL)
        {
            // cout<<"start"<<command[j]<<endl;
            if(pipe(fd)<0)
            {
                cout<<"Pipe could not be intialised\n";
                return;
            }
            pid=fork();
            if(pid==0)
            {
                if(j!=0)
                {
                    dup2(prev,0);
                    // dup2(fd[0],0);
                    
                }
              
                if(command[j+1])
                    dup2(fd[1],1);
                close(fd[0]);
                close(fd[1]);
                char *p=command[j];
                char *argv1[1000];
                for(int i=0;i<1000;i++)
                {
                    argv1[i]=strsep(&p," ");
                    if(argv1[i]==NULL)
                        break;
                    if(strlen(argv1[i])==0)
                        i--;
                }
                int e=execvp(argv1[0],argv1);

                // cout<<"end"<<command[j]<<endl;

            }
            else if(pid<0)
                cout<<"could not fork\n";
            else
            {

                
                wait(NULL);
                //close(prev);
                prev=fd[0];
                close(fd[1]);
                
                j++;
            }
            

        }
    }
}

vector<string> global1;
int main()
{
	string s;
	while(1)
	{

		int flag=0,flag1=0;
		cout<<"[akash@akash-3052-root]$ ";
		getline(cin,s);
		vector<string> cmd;
		
		global1.push_back(s);
		stringstream ss(s);
		string word;
		//storing input in cmd vector
		while(ss>>word)
		{
			
			cmd.push_back(word);
		}
		if(s.compare("history")==0)
			flag=5;

		//storing input in argv1 char arry from cmd vector
		int n1=cmd.size();
		// cout<<n<<endl;
		// char *argv1[n+1];
		// for(int i=0;i<n;i++)
		// {
		// 	int n=cmd[i].size();  
		// 	argv1[i]=(char *)malloc((n+1)*sizeof(char));
		// 	strcpy(argv1[i],cmd[i].c_str());
		// }
		// argv1[n]=NULL;

		int n=s.length();
		char str[n+1];
		strcpy(str,s.c_str());
		char *p=str;
		char *argv1[1000];
		for(int i=0;i<1000;i++)
		{
			argv1[i]=strsep(&p," ");
			if(argv1[i]==NULL)
				break;
			if(strlen(argv1[i])==0)
				i--;
		}

		// for(int i=0;i<n;i++)
		// 	cout<<s[i]<<" ";
		//code to handle pipe(if pipe is present)
		// vector<string>::iterator it,it2;
		// it=find(cmd.begin(),cmd.end(),"|");
		
		for(int i=0;i<n;i++)
		{
			if(s[i]=='|')
			{
				// cout<<"pipe";
				flag=1;
				break;
			}
			if(s[i]=='>')
			{	
				// cout<<"direction";
				flag=2;
				if(s[i+1]=='>')
				{
					flag=3;
					break;
				}
				break;
			}
			if(s[i]=='c')
			{
				if(s[i+1]='d')
				{
					flag=4;
					break;
				}
			}
			

		}

		if(flag==1)
		{
			for(int i=0;i<n;i++)
			{
				if(s[i]=='>')
				{	
					//cout<<"direction";
					flag1=1;
					if(s[i+1]=='>')
					{
						flag1=2;
						break;
					}
					break;
				}
			}
		}

		//if pipe is preset
		if(flag==1)
		{
			// cout<<"flag 1";
			// cout<<"if loop";
			int n=s.length();
			char str[n+1];
			strcpy(str,s.c_str());
			char *p =str;
			char *command[1000];
			for(int i=0;i<1000;i++)
			{
				command[i]=strsep(&p,"|");
				if(command[i]==NULL)
					break;
			}
			piperun(command,flag1);
			
		}

		//if redirection operator is present
		else if(flag==2)
		{
			// cout<<"flag 2";
			int n=s.length();
			char str[n+1];
			strcpy(str,s.c_str());
			char *p =str;
			char *command[1000];
			for(int i=0;i<1000;i++)
			{
				command[i]=strsep(&p,">");
				if(command[i]==NULL)
					break;
				if(strlen(command[i])==0)
					i--;
			}

			// for(int i=0;command[i]!=NULL;i++)
			// 	cout<<command[i]<<" ";
			// cout<<endl;

			// int j=0;
			// while(command[j]!=NULL)
			// {
			// 	char *p=command[j];
			// 	char *argv1[1000];
			// 	for(int i=0;i<1000;i++)
			// 	{
			// 		argv1[i]=strsep(&p," ");
			// 		if(argv1[i]==NULL)
			// 			break;
			// 		if(strlen(argv1[i])==0)
			// 			i--;
			// 	}
			// 	j++;

			// }
			redirec(command);
			
		}

		else if(flag==3)
		{
			int n=s.length();
			char str[n+1];
			strcpy(str,s.c_str());
			char *command[1000];
			char *p=str;
			for(int i=0;i<1000;i++)
			{
				command[i]=strsep(&p,">>");
				if(command[i]==NULL)
					break;
				if(strlen(command[i])==0)
					i--;
			}

			// for(int i=0;command[i]!=NULL;i++)
			// 	cout<<command[i]<<" ";
			// cout<<endl;
			appendrun(command);


		}
		else if(flag==4)
		{
			int n=s.length();
			char str[n+1];
			strcpy(str,s.c_str());
			char *p=str;
			char *argv1[1000];
			for(int i=0;i<1000;i++)
			{
				argv1[i]=strsep(&p," ");
				if(argv1[i]==NULL)
					break;
				if(strlen(argv1[i])==0)
					i--;
			}
			// for(int i=0;argv1[i]!=NULL;i++)
			// 	cout<<argv1[i]<<endl;
			chdir(argv1[1]);
		}

		else if(flag==5)
		{
			for(int i=0;i<global1.size();i++)
			{
				cout<<global1[i]<<endl;
			}
		}

		//if pipe and redirection is not present
		else if(flag==0)
		{
			// cout<<"flag 0";
			// cout<<"else loop";
			int pid=fork();
			if(pid==0)
			{
			// int i=execve(res,argv1,environ);
				int i=execvp(argv1[0],argv1);
				if(i==-1)
					cout<<"errror in running program";
				cout<<endl;
			}
			else if(pid<0)
			{
				cout<<"Fork errror..";
			}
			//parent process
			else
			{

				wait(NULL);
			}
			
		}
	}
	return 0;
}