#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int dirsize(char *dirName, int deep){
    DIR *dir;
    struct dirent *ptr;
    char *dname;
    struct stat st;
    int totalSize = 0;
    int subSize;

    //递归深度大于10
    if(++deep > 2){
        return 0;
    }

    if((dir = opendir(dirName)) == NULL){
        printf("open dir failed: %s\n", dirName);
        return -1;
    }

    //进入下一级目录
    chdir(dirName);

    while((ptr = readdir(dir)) != NULL){
        dname = ptr->d_name;
        printf("%s \n", dname);
        if(strcmp(dname, ".") == 0 || (strcmp(dname, "..") == 0 || (strcmp(dname, ".git1")==0) )){
            continue;
        }else{
            lstat(dname, &st);
            //普通文件
            if(S_ISREG(st.st_mode)){
                totalSize += st.st_size;
            }
            //文件夹
            else if(S_ISDIR(st.st_mode)){
                subSize = dirsize(dname, deep);
                if( subSize == -1){
                    closedir(dir);
                    chdir("..");
                    return -1;
                }else{
                    totalSize += subSize;
                }
            }
        }
    }
    closedir(dir);
    //退回上一级目录
    chdir("..");
    return totalSize;
}


int main(int argc, char *argv[]){
    int totalSize;
    if(argc < 2){
        printf("argument error \n");
        return -1;
    }
    totalSize = dirsize(argv[1], 0);
    if(totalSize < 0){
        printf("failed\n");
        return -2;
    }
    printf("%d\n", totalSize);
    return totalSize;
}