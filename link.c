#include <stdio.h>
#include <stdlib.h>
 struct Link {
    int elem;
    struct Link* next;
};
struct Link* initLink() {
    int i = 0; 
    struct Link* p = NULL;//在节点投入使用前都是这样
    struct Link* temp = (struct Link*)malloc(sizeof(struct Link));
    temp->elem = 0;
    temp->next = NULL;
    p = temp;
    for (i = 1;i < 5; i++){
        struct Link* a = (struct Link*)malloc(sizeof(struct Link));
        a->elem = i;
        a->next = NULL;
        temp->next = a;
        temp->next = a;
        temp = temp->next;
    }
    return p;

}

    struct Link* insertElem(struct Link* p, int elem, int add){
            if(add == 1){
                struct Link* c =(struct Link*)malloc(sizeof(struct Link));
                c->elem = elem;
                c->next = p;
                p = c;
                return p;
            }
        else {
            int i;
            struct Link* c = NULL; 
            struct Link* temp = p;
            for (i = 1; i < add-1; i++) {
                temp = temp->next;
                if (temp == NULL) {
                    printf("插入位置无效\n");
                    return p;
                }
            }
            c =(struct Link*)malloc(sizeof(struct Link));
            c->elem = elem;
            c->next = temp->next;
            temp->next = c;
            return p;
            }
            
        }
        //删除
        int delElem(struct Link** p, int elem) {
            struct Link* del = NULL, *temp = *p;
            int find = 0;
            while (temp->next){
                if (temp->next->elem == elem){
                    find = 1;
                    break;
                }
                temp = temp->next;
            }
            if (find == 0) {
                return -1;
            }
            else{
                del = temp->next;
                temp->next = temp->next->next;
                free(del);
                return 1;
            }
        }
        //查找
        int selectElem(struct Link* p, int elem) {
            struct Link* del = NULL, *temp = p;
            int find = 0;
            while (temp->next) {
                if (temp->next->elem == elem) {
                    find = 1;
                    break;
                }
                temp = temp->next;
            } 
            if (find == 0) {
                return -1;
            }
            else
            {
                del = temp->next;
                temp->next = temp->next->next;
                free(del);
                return 1;
            }
        } 


   //输出链表中各个节点的元素       
void display(struct Link* p) {
    p = p->next;
    while (p) {
        printf("%d",p->elem);
        p = p->next;
    }
    printf("\n");
}
//释放链表
void  Link_free(struct Link* p) {
    struct Link* fr = NULL;
    while (p->next)
    {
        fr = p->next;
        p->next = p->next->next;
        free(fr);
    }
    free(p);
}
int main(){
    
    struct Link* p = NULL;
    printf("初始化链表为\n");
    p = initLink();
    display(p);
    printf("在第3的位置上添加 6: \n");
    insertElem(p, 6 , 3);
    display(p);
    printf("删除4: \n");
    delElem(&p, 4);
    display(p);
    printf ("查找元素2:%d\n",selectElem(p, 2));
    
    return 0;
}