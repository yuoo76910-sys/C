#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdatomic.h>

#define NUM_THREADS 8             //定义线程数量为8个
#define READ_SIZE 1048576         //每次读取的大小
#define LOOKAHEAD_SIZE 1024       //额外多读的字节数防止在单词里面 包Z哼读取到完整的单词

typedef struct {
    int fd;                       //定义文件描述符
    off_t offset;                //文件偏移量 off_t能兼容不同大小的文件 比int大 管在哪
    size_t length;                //要读取的长度 管多长
    int word_count;              //记录单词数量
}ThreadData;                      //类似数据包 后面应用更方便

pthread_mutex_t lock;
void *count_words(void *arg) {    //线程执行的函数 计算文本中的单词数量
    ThreadData *data = (ThreadData *)arg; //将传入的void*参数转换为ThreadData类型 带上态度面具 因为void只能识别void*类型
    int fd = data->fd;            //获取文件描述符
    off_t offset = data->offset;  //获取线程处理的起始偏移量
    size_t length = data->length; //获取线程要处理的总字节长度
    int count = 0;                // 初始化当前线程的单词计数器
    int in_word = 0;             //标记是否处于单词中（0=不在 1=在）

    size_t buffer_size = READ_SIZE + LOOKAHEAD_SIZE + 1;
    char *buffer = (char *)malloc(buffer_size + 1);//缓冲区=读取块+预读块+结束符
    if (buffer == NULL) {
        perror("Error allocating memory");
        return NULL;               //申请失败 退出线程
    }

    while(length > 0) {
        size_t to_read = 0;

        if (to_read = length > READ_SIZE){
            to_read = READ_SIZE;
        } else{
            to_read = length;
        }

        //read_size pread实际从文件读到的大小 
        ssize_t read_size = pread(fd, buffer, to_read +LOOKAHEAD_SIZE,offset);//要读的文件 要存的地方 要读多少 从哪开始读 read_size 读的大小
        
        if (read_size < 0) {
            perror("Error reading file");
            free(buffer);
            return NULL;                        //读取失败处理
        }

    //请求读取的字节数大于实际读取量 到数据末尾
        if ( to_read + LOOKAHEAD_SIZE > read_size) {    //要读的比读的大
        buffer[read_size] = '\0';               //到了文件末尾无意外结束\0是结束符
    }

    for (ssize_t i = 0;i < read_size; i++) {
        //遇到空白字符 且在之前单词中 单词结束
        if (isspace (buffer[i]))  {
            if (in_word) {
                count++;
                in_word = 0;
            } 
        }else {
    //遇到非空白字符 进入单词中
            in_word = 1;
        }
    }
    //更新进度 ：偏移量后移，剩余长度减少
        offset += read_size;
        length -=read_size;
    }
    //处理缓冲区末尾的单词 （循环结束仍在单词中）
    if (in_word) {
        count++;
    }
    atomic_store(&data->word_count , count);   //将当前线程的统计结果写入结构体
    free(buffer);                               //释放缓冲区内存
    return NULL;                                //线程执行完毕退出
}
int main() {
    printf("Opening file...\n");
    int fd = open("english.txt", O_RDONLY);     //打开文件
    if (fd < 0) {
        perror("ERROR opening file");
        abort();                                // 如果打开文件失败，终止程序
    }

    printf("File opened successfully.\n");

        struct stat st;
        if (fstat(fd, &st) < 0) {
            perror("Error getting file size");
            close(fd);
            abort();                            //如果获取文件大小失败，终止程序
        }
        off_t file_size = st.st_size;           //获取文件大小

        printf("FIle size: %ld bytes\n", file_size);

        pthread_t threads[NUM_THREADS];         //线程标识符数组
        ThreadData thread_data[NUM_THREADS];    //线程数据结构数组

        size_t chunk_size = file_size / NUM_THREADS;//计算每个线程处理的文本块大小
        for (int i = 0; i < NUM_THREADS; i++) {
            printf("Creating yhread %d..\n", i);
            thread_data[i].fd = fd;             //设置文件描述符
            thread_data[i].offset = i * chunk_size; //设置文件偏移量
            thread_data[i].length = (i == NUM_THREADS - 1) ? file_size - i * chunk_size : chunk_size;
            atomic_init(&thread_data[i].word_count, 0);    //初始化单词计数（原子操作）
            int ret = pthread_create(&threads[i],NULL, count_words, &thread_data[i]);//创建线程
            if (ret !=0) {
                perror("Error creating thread");
                close(fd);
                abort(); //如果创建线程失败，终止程序
            }
            printf("Thread %d created successfully.\n", i);
        }

        int total_word_count = 0;   //初始化单词计数
        for (int i = 0; i< NUM_THREADS; i++) {
            printf("Joining thread %d...\n", i);
            pthread_join(threads[i], NULL); //等待线程结束
            printf("Thread %d joined. Word count: %d\n", i, atomic_load(&thread_data[i].word_count));
            total_word_count += atomic_load(&thread_data[i].word_count); //累计总单词计数
        }
        close(fd); //关闭文件

        printf("Total word count: %d\n", total_word_count); //输出单词计数结果

        return 0;
    }
