#include <stdio.h>
#include <stdlib.h>

#define LENGTH 255
#define HIGH 255
#define SONS 1024
#define L 10
#define LEN 70000
#define R 2100

//struttura di tutti i nodi
typedef struct node{
    char name[LENGTH];
    int max_sons;     //controlla che il numero di figli sia minore di 1024
    struct node *next_brother; //punta al fratello
    struct node *left_son; //punta al figlio più a sinistra, puntatore de padre
    char text[LENGTH];
    int file_flag;
    char *road;
    int alloc;
	}node_t;

typedef struct so{
    char street[R];
    struct so *pun;
}ord_t;

struct so begin;
ord_t *pr=NULL;
struct node root;
int len=0;

void copy_string(char *str1, const char *str2){
    len =0;
    for(len; str2[len]!='\0'; len++)
        str1[len]=str2[len];
    str1[len]='\0';
    return;
}

int compare_string(char* str1,const char* str2){
    int i=0;
    int result;
    while(str1[i]!='\0' && str2[i]!='\0' && str1[i]==str2[i]) //confroto le stringhe
        i++;
    if(str1[i]=='\0' && str2[i]=='\0') //se le stringhe hanno gli stessi caratteri e sono lunghe uguali
        result = 0;
    else  //in tutti gli atri casi non accetto
        result = 1;
    return result;
}

int c_string(char *str1, char* str2){
    int i=0;
    int result;
    while(str1[i]!='\0' && str2[i]!='\0' && str1[i]==str2[i]) //confroto le stringhe
        i++;
    if(str1[i]!=str2[i] && str1[i]!='\0' && str2[i]!='\0'){
        if(str1[i]>str2[i]){           //se str2 precede alfabeticamente str1
            result=1;
        }
        else if(str1[i]<str2[i]){
            result=-1;
        }
    }
    return result;
}

void concat(char* str1,char*str2){
    int i=0;
    int k=0;
    while(str1[i]!='\0')
        i++;
    for(i,k; str2[k]!='\0'; i++,k++)
        str1[i]=str2[k];
    str1[i]='\0';
    return;
}

void create_dir(char* str){
    node_t *father = &root; // questo puntatore punta al padre ad ogni giro
    node_t *search; //serve per cercare il nodo
    node_t *newnode;
    node_t *check;
    int q=0;
    int k=0;
    int j=0; //conta il numero di figli del padre che non corrispodnono a quello cercato
    int h=0; //conta l'altezza dell'albero
    int r=0;
    char dir[LENGTH];
    char s[L];
    s[0]='\0';
    char c[L];
    c[0]='/';
    c[1]='\0';
    for(k; str[k]!='\0'; k++){
        q=0;
        j=0; //ad ogni giro azzero il conter per i figli
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++){
           if(q==255){
                printf("no\n");
                return;
            }
            dir[q]=str[k];
        }
        dir[q]='\0';
        h++;
        if(h==256){   //se l'altezza supera quella pre stabilita di 255
            printf("no\n");
            return;
        }

        if(str[k]=='/'){  //non devo inserire ma devo cercare il percorso
            if(father->max_sons==0){ //se il padre non ha figli ma io ho comunque un suo figlio nel percorso
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0){ //il padre è il figlio sinistro
                father=father->left_son;
            }
            else{ //il padre non è il figlio sinistro quindi devo cercarlo
                if(father->max_sons==1 && compare_string(father->left_son->name, dir)==1){ //se il padre ha solo il figlio sinistro ma questo non corrisponde a quello cercato
                    printf("no\n");
                    return;
                }
                else{
                    search=father->left_son->next_brother;
                    j++;
                    while(compare_string(search->name,dir)==1){
                        search=search->next_brother;
                        j++;
                        if (father->max_sons==j){
                        printf("no\n");
                        return;
                        }
                    }
                }
                father=search;
            }
        }
        else{
            newnode =(struct node*)malloc(sizeof(struct node));  //ritorna l'indirizzo di mem di dove è allocato lo spazio
            if (father->max_sons==0 && father->file_flag==0){
                copy_string(newnode->name, dir);
                father->max_sons=1;
                father->left_son=newnode;
                newnode->max_sons=0;
                newnode->file_flag=0;
                newnode->left_son=NULL;
                newnode->next_brother=NULL;
                newnode->alloc=0;
                printf("ok\n");
                return;
            }
            else{
                check=father->left_son;
                for(r=0; r<father->max_sons;r++){  //cambiato r non parte da 1 ma da 0
                    if(compare_string(check->name,dir)==0){
                        printf("no\n");
                        return;
                    }
                    check=check->next_brother;
                }
                if(father->max_sons<1024 && father->file_flag==0){
                    copy_string(newnode->name, dir);
                    newnode->max_sons=0;
                    father->max_sons++;
                    newnode->next_brother=father->left_son;
                    father->left_son=newnode;
                    newnode->file_flag=0;
                    newnode->max_sons=0;
                    newnode->left_son=NULL;
                    newnode->alloc=0;
                    printf("ok\n");
                    return;
                }
                else{
                    printf("no\n");
                    return;
                }
            }
        }
    }
}

void delete_(char* str){
    node_t *father=&root;
    node_t *search;
    node_t *before=&root; //mi serve per salvare il nodo padre di quello che devo cancellare
    node_t *prec=&root;  //necessario per avere l'elemento precedente quello che deve essere cancellato
    int k=0;
    int q=0;
    int j=0;
    char dir[LENGTH];
    for(k; str[k]!='\0'; k++){
        q=0;
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++){
            if(q==255){
                printf("no\n");
                return;
            }
            dir[q]=str[k];
        }
        dir[q]='\0';
        if (str[k]=='/'){
            if(father->max_sons==0){
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0){ //il nuovo elemento cercato è il figlio sinistro dell'elemento trovato al giro precedente
                father=father->left_son;
            }
            else{
                search=father->left_son;
                while(compare_string(search->name,dir)==1){ //nel caso in cui l'elemento non è il figlio sinistro scorro la lista dei fratelli fino a trovarlo
                    j++;
                    if (father->max_sons==j){ //nel caso in cui non si sia trovato il figlio
                        printf("no\n");
                        return;
                    }
                    search=search->next_brother;
                }
                father=search;
                j=0;
            }
        }
        else{
             if(father->max_sons==0){
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0){ //il nuovo elemento cercato è il figlio sinistro dell'elemento trovato al giro precedente
                search=father->left_son;
                if(search->max_sons==0){ //se il nodo che voglio cancelare non ha figli allora lo cancello
                    father->left_son=search->next_brother;
                    free(search);
                    father->max_sons--; //decremento il counter del nodo padre
                    printf("ok\n");
                    return;
                }
                else { //se l'ultimo elemento del percorso  ha fgli allora non posso cancellarlo
                    printf("no\n");
                    return;
                }
            }
            else{
                prec=father;
                search=father->left_son;
                while(compare_string(search->name,dir)==1){ //nel caso in cui l'elemento non è il figlio sinistro scorro la lista dei fratelli fino a trovarlo
                    j++;
                    if (father->max_sons==j){ //nel caso in cui non si sia trovato il figlio
                        printf("no\n");
                        return;
                    }
                    prec=search;
                    search=search->next_brother;
                }
                j=0;
                if(search->max_sons==0){ //se il nodo che voglio cancelare non ha figli allora lo cancello
                    prec->next_brother=search->next_brother;
                    free(search);
                    father->max_sons--; //decremento il counter del nodo padre
                    printf("ok\n");
                    return;
                }
                else{
                    printf("no\n");
                    return;
                }
            }
        }
    }
}

//funzione usata per eliminare gli elementi
void delete_list(node_t *str, int r){  //r, numero di figli della cartella che devo cancellare
    node_t *newlist; //nodo con cui scorro nella nuova lista
    node_t *del=str; //nodo in cui salvo il primo puntatore della lista che deo cancellare
    node_t *next=str; //nodo che mi consente di scorrere nella lista dei figli
    node_t *head=NULL; //nodo in cui salvo il primo nodo della lista formata dai figli
    int i=0;
    int count=0;
    for (i; i<r; i++){ //fintanto che ho un numero di figli
        next=del;
        if(next->max_sons>0){
            if(head==NULL){ //se sto inserendo il primo elemento della mia nuova lista
                head=next->left_son;
                newlist=head;
                next->max_sons--; //decremento il numero di figli del nodo finchè non diventa zero e mi fa uscire dal ciclo;
                count++; //incremento il counter che considera gli elementi della nuova lista
            }
            else{
                newlist->next_brother=next->left_son;
                newlist=newlist->next_brother;
                next->max_sons--;
                count++;
            }
            while(next->max_sons>0){
                newlist=newlist->next_brother;
                next->max_sons--;
                count++;
            }
            del=next->next_brother;
            free(next);
        }
        else{
            del=next->next_brother;
            free(next);
        }
    }
    if(head!=NULL)
        delete_list(head,count);
    else
        return;
}


void delete_r(char* str){
    node_t *father=&root;
    node_t *search;
    node_t *before=&root;
    node_t *prec;
    int k=0;
    int q=0;
    int j=0;
    char dir[LENGTH];
    for(k; str[k]!='\0'; k++){
        q=0;
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++)
            dir[q]=str[k];
        dir[q]='\0';
         if (str[k]=='/' || str[k]=='\0'){
            if(compare_string(father->left_son->name, dir)==0){ //l'elemento del percorso cercato è il figlio sinistro
                prec=father;
                father=father->left_son;
                if (str[k]=='/')
                    before= father;
            }
            else{
                prec=father->left_son; //salvo il fratello precedente
                search=father->left_son->next_brother;
                j++;
                while(compare_string(search->name,dir)==1){ //se non è il figlio sinistro procedo tra i fratelli
                    prec=search;
                    search=search->next_brother;
                    j++;
                    if (father->max_sons==j){ //nel caso in cui non si sia trovato il figlio
                        printf("no\n");
                        return;
                    }
                }
                father=search;
                j=0;
                if (str[k]=='/')
                        before= search;
            }
            if(str[k]=='/' && father->max_sons==0){ //se elemento del percorso non ha figli ma non è l'ultimo non posso proseguire
                printf("no\n");
                return;
            }
            if(str[k]=='\0' && father->max_sons==0){ //se il nodo che voglio cancelare non ha figli allora lo cancello
                if(prec->max_sons>0 && compare_string(prec->left_son->name,dir)==0)
                    prec->left_son=father->next_brother;
                else if(compare_string(prec->next_brother->name, dir)==0)
                    prec->next_brother=father->next_brother;
                free(father);
                before->max_sons--;
                printf("ok\n");
                return;
            } //fino a qui uguale alla delete, ora parte aggiuntiva
            else if(str[k]=='\0' && father->max_sons!=0){ //se il nodo ha figli cancello anche quelli
                if(prec->max_sons>0 && compare_string(prec->left_son->name,dir)==0)
                    prec->left_son=father->next_brother;
                else if(compare_string(prec->next_brother->name, dir)==0)
                    prec->next_brother=father->next_brother;
                delete_list(father->left_son, father->max_sons);
                free(father);
                before->max_sons--;
                printf("ok\n");
                return;
            }
        }
        if(str[k]=='\0')
            k--;
    }
    return;
}


void create(char* str){
    node_t *father=&root;
    node_t *search;
    node_t *newnode;
    node_t *check;
    char s[L];
    s[0]='\0';
    int k=0;
    int q=0;
    int h=0;
    int j=0;
    int r=0;
    char dir[LENGTH];
    char c[L];
    c[0]='/';
    c[1]='\0';
    for(k; str[k]!='\0'; k++){
        q=0;
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++)
            dir[q]=str[k];
        dir[q]='\0';
        h++;
        if(h==256){   //se l'altezza supera quella pre stabilita di 255
            printf("no\n");
            return;
        }
        if(str[k]=='\0') //con l'if posso controllare la divisione della stringa
            k--;
        if (str[k]=='/'){
            if(father->max_sons==0){
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0) //il padre è il figlio sinistro
                father=father->left_son;
            else{ //il padre non è il figlio sinistro quindi devo cercarlo
                if(father->max_sons==1 && compare_string(father->left_son->name, dir)==1){
                    printf("no\n");
                    return;
                }
                else{
                    search=father->left_son->next_brother;
                    j++;
                    while(compare_string(search->name,dir)==1){
                        search=search->next_brother;
                        j++;
                        if (father->max_sons==j){
                        printf("no\n");
                        return;
                        }
                    }
                }
                father=search;
                j=0;
            }
        }
        else{
            newnode =(struct node*)malloc(sizeof(struct node));  //ritorna l'indirizzo di mem di dove è allocato lo spazio
            if (father->max_sons==0 && father->file_flag!=1){
                copy_string(newnode->name, dir);
                copy_string(newnode->text, s);
                father->max_sons=1;
                father->left_son=newnode;
                newnode->file_flag=1;
                newnode->max_sons=0;
                newnode->left_son=NULL;
                newnode->next_brother=NULL;
                newnode->alloc=0;
                printf("ok\n");
                return;
            }
            else{
                check=father->left_son;
                for(r=0; r<father->max_sons;r++){ //ho cambiato il valore di r da 0 a 1
                    if(compare_string(check->name,dir)==0){
                        printf("no\n");
                        return;
                    }
                    check=check->next_brother;
                }
                if(father->max_sons<1024 && father->file_flag!=1){
                    copy_string(newnode->name, dir);
                    copy_string(newnode->text, s);
                    father->max_sons++;
                    newnode->next_brother=father->left_son;
                    father->left_son=newnode;
                    newnode->file_flag=1;
                    newnode->max_sons=0;
                    newnode->left_son=NULL;
                    newnode->alloc=0;
                    printf("ok\n");
                    return;
                }
                else{
                    printf("no\n");
                    return;
                }
            }

        }
    }
}


void read(char* str){
    node_t *father=&root;
    node_t *search;
    int k=0;
    int q=0;
    int h=0;
    int j=0;
    char dir[LENGTH];
    char s[LENGTH];
    s[0]='\0';
    for(k; str[k]!='\0'; k++){
        q=0;
        h++;
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++)  //ad ogni giro salvo in dir il nome del nuovo pezzo di percorso
            dir[q]=str[k];
        dir[q]='\0';
        if(h==256){   //se l'altezza supera quella pre stabilita di 255
            printf("no\n");
            return;
        }
         if(str[k]=='/' || str[k]=='\0'){  //devo cercare il percorso
            if(father->max_sons==0){ //se il padre non ha figli ma io ho comunque un suo figlio nel percorso
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0) //il padre è il figlio sinistro
                father=father->left_son;
            else{ //il padre non è il figlio sinistro quindi devo cercarlo
                if(father->max_sons==1 && compare_string(father->left_son->name, dir)==1){
                    printf("no\n");
                    return;
                }
                else{
                    search=father->left_son->next_brother;
                    j++;
                    while(compare_string(search->name,dir)==1){
                        search=search->next_brother;
                        j++;
                        if (father->max_sons==j){ //nel caso in cui non si sia trovato il figlio
                        printf("no\n");
                        return;
                        }
                    }
                }
                father=search;
                j=0;
                }
            }
        if(str[k]=='\0' && father->file_flag==1){
            printf("contenuto %s\n", father->text);
            k--;
            return;
        }
        else if(str[k]=='\0' && father->file_flag==0){
            printf("no\n");
            return;
        }
    }
}


void write(char* str, char* str2){
    node_t *father=&root;
    node_t *search;
    int k=0;
    int q=0;
    int h=0;
    int j=0;
    char dir[LENGTH];
    for(k; str[k]!='\0'; k++){
        q=0;
        for(q,k; str[k]!='/' && str[k]!='\0'; k++,q++)  //ad ogni giro salvo in dir il nome del nuovo pezzo di percorso
            dir[q]=str[k];
        dir[q]='\0';
        h++;
        if(h==256){   //se l'altezza supera quella pre stabilita di 255
            printf("no\n");
            return;
        }
         if(str[k]=='/' || str[k]=='\0'){  //devo cercare il percorso
             if(father->max_sons==0){ //se il padre non ha figli ma io ho comunque un suo figlio nel percorso
                printf("no\n");
                return;
            }
            if(compare_string(father->left_son->name, dir)==0) //il padre è il figlio sinistro
                father=father->left_son;
            else{ //il padre non è il figlio sinistro quindi devo cercarlo
                if(father->max_sons==1 && compare_string(father->left_son->name, dir)==1){
                    printf("no\n");
                    return;
                }
                else{
                    search=father->left_son->next_brother;
                    j++;
                    while(compare_string(search->name,dir)==1){
                        search=search->next_brother;
                        j++;
                        if (father->max_sons==j){ //nel caso in cui non si sia trovato il figlio
                        printf("no\n");
                        return;
                        }
                    }
                }
                father=search;
                j=0;
                }
            }
        if(str[k]=='\0' && father->file_flag==1){
            copy_string(father->text, str2);
            printf("ok %d\n", len);
            k--;
        }
        else if(str[k]=='\0' && father->file_flag!=1){
            printf("no\n");
            return;
        }
    }
}

void save(char* str){
    ord_t *start=&begin;
    ord_t *newnode;
    ord_t *search;
    char s[L];
    s[0]='\0';
    newnode=(struct so*)malloc(sizeof(struct so));
    newnode->pun=NULL;
    if(start->pun==NULL){
        copy_string(newnode->street,str);
        start->pun=newnode;
        pr=newnode;
    }
    else{
        if(c_string(pr->street, str)==1){//se str precede alfabeticamente string->street
            newnode->pun=start->pun;
            start->pun=newnode;
            copy_string(newnode->street, str);
        }
        else if(c_string(pr->street, str)==-1){ //se str segue string->street la salvo in fondo alla lista
            for(search=start; search->pun!=NULL; search=search->pun)
                ;
            search->pun=newnode;
            copy_string(newnode->street, str);
        }
    }
    return;
}

//si trovano tutti i percorsi
void on_the_road(node_t *father, char* dir){
    node_t *del=father->left_son;
    node_t *next=father->left_son;
    int i=0;
    char c[L];
    c[0]='/';
    c[1]='\0';
    for(i; i<father->max_sons; i++){
        next=del;
        if(next->alloc==0){
            next->road=(char*)malloc(sizeof(char)*2100);
            next->alloc=1;
            copy_string(next->road, father->road);
            concat(next->road,c);
            concat(next->road,next->name);
        }
        if(compare_string(next->name, dir)==0){
            save(next->road);
            }
        if(next->max_sons>0){
            on_the_road(next,dir);
            del=next->next_brother;
        }
        else{
            del=next->next_brother;
        }
    }
    return;
}

void find(char* path){
    node_t *father=&root;
    ord_t *go;
    go=&begin;
    go->pun=NULL;
    ord_t *del;
    char s[L];
    s[0]='\0';
    if(father->alloc==0){
        father->road=(char*)malloc(sizeof(char)*1);
        father->alloc=1;
        copy_string(father->road, s);
    }
    on_the_road(father, path);
    if(go->pun!=NULL){
        go=go->pun;
        while(go!=NULL){
                printf("ok %s\n", go->street);
                del=go->pun;
                free(go);
                go=del;
        }
        return;
    }
    else if(compare_string(go->street,s)==0){
        printf("no\n");
        return;
    }
}

void main(){
    char str[LEN];
    char *str1="create_dir";
    char *str2="delete";
    char *str3="delete_r";
    char *str4="exit";
    char *str5="create";
    char *str6="read";
    char *str7="write";
    char *str8="find";
    char command[L];
    char path[LEN];
    char text[LENGTH];
    char s[L];
    s[0]='\0';
    root.max_sons=0; //la radice non ha figli in origine
    root.file_flag=0;
    root.left_son=NULL;
    root.next_brother=NULL;
    root.alloc=0;
    copy_string(root.name, s);
    do{
        gets(str);
        char *p=str;
    //separo la stringa inserita in due sottostringhe, una con il comando; l'altra con il percorso
        int i=0;
        int k=0;
        for(i,k; p[i]!=' '; i++,k++)
            command[k]=p[i];
        command[k]='\0';
        k=0;
        while(p[i]==' ' || p[i]=='/')
            i++;
        for(i,k; p[i]!='\0' && p[i]!=' '; i++,k++)
            path[k]=p[i];
        path[k]='\0';
        k=0;
        if(p[i]!='\0'){
            while(p[i]==' ' || p[i]=='"' )
                i++;
            for(i,k; p[i]!='"'; i++,k++)
                text[k]=p[i];
            text[k]='\0';
        }
    //scelgo quale operazione eseguire
        if(compare_string(command,str1)==0)    //1. create_dir creo la directory nell'albero
            create_dir(path);
        else if(compare_string(command,str2)==0)//2. cancello la directory solo se foglia
            delete_(path);
        else if(compare_string(command,str3)==0) //3. cancello l'intero percorso
            delete_r(path);
        else if(compare_string(command,str5)==0) //4. creo un file
            create(path);
        else if(compare_string(command,str6)==0) //5. leggo un file
            read(path);
        else if(compare_string(command,str7)==0) //6. scrivo in un file
            write(path, text);
        else if(compare_string(command,str8)==0) //7. cerco un elemento
            find(path);
    }while(compare_string(command, str4)!=0);
    return;
}

