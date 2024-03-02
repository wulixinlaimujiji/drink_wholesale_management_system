#include "public.h"
extern Manager* manager;
extern User* user_head;
extern Drink* drink_head;
extern WholesaleRecord* wholesaleRecord_head;
extern PurchaseRecord* purchaseRecord_head;

///系统初始化
//创建管理员记录
Manager* CreatManager() {
    //打开管理员文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("manager.txt", "a+")) == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }
    //若打开成功，则读取文件,创建管理员账号
    //检测是否空文件
    getc(fp);
    if (feof(fp)) {
        return NULL;
    }
    else {
        rewind(fp);
    }
    //创建结点
    Manager* manager = (Manager*)malloc(sizeof(Manager));
    if (!manager) {
        printf("内存分配失败\n");
        return NULL;
    }
    else {
        fscanf(fp, "%s", manager->ID);
        fscanf(fp, "%s", manager->password);
        fscanf(fp, "%s", manager->Tel);
        fscanf(fp, "%f", &manager->fund);
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
    //返回管理员账号
    return manager;
}
//创建用户链表
User* CreatUserList() {
    /*创建哨兵结点*/
    User* head = (User*)malloc(sizeof(User));
    User* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    /*打开用户文件*/
    FILE* fp;
    /*若打开失败，则返回*/
    if ((fp = fopen("users.txt", "a+")) == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }
    /*若打开成功，则读取文件，创建用户链表*/
    //检测是否空文件
    getc(fp);
    //空文件则关闭文件并返回
    if (feof(fp)) {
        if (fclose(fp) != 0) {
            printf("文件关闭失败\n");
        }
        return head;
    }
        //文件非空则将指针移回原位
    else {
        rewind(fp);
    }
    //读取文件，创建链表
    while (!feof(fp)) {
        //创建结点
        User* temp = (User*)malloc(sizeof(User));
        if (!temp) {
            printf("内存分配失败\n");
            return NULL;
        }
        else {
            fscanf(fp, "%s", temp->ID);//客户账号
            fscanf(fp, "%s", temp->password);//客户密码
            fscanf(fp, "%s", temp->name);//营业网点名称
            fscanf(fp, "%d", &temp->level);//客户级别
            fscanf(fp, "%s", temp->address);//客户地址
            fscanf(fp, "%s", temp->Tel);//客户联系方式
            fscanf(fp, "%f", &temp->total_funding);//账户余额
            fscanf(fp, "%f", &temp->total_consumption);//总消费
            temp->next = NULL;
            //加入链表
            tail->next = temp;
            tail = temp;
        }
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
    //删除最后一个冗余结点
    User* p = head;
    while (p->next != tail) {
        p = p->next;
    }
    p->next = NULL;
    free(tail);
    tail = NULL;
    //返回头结点
    return head;
}
//创建酒水链表
Drink* CreatDrinkList() {
    /*创建哨兵结点*/
    Drink* head = (Drink*)malloc(sizeof(Drink));
    Drink* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    /*打开酒水文件*/
    FILE* fp;
    /*若打开失败，则返回*/
    if ((fp = fopen("drink.txt", "a+")) == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }
    /*若打开成功，则读取文件，创建酒水链表*/
    //检测是否空文件
    getc(fp);
    //空文件则关闭文件并返回
    if (feof(fp)) {
        if (fclose(fp) != 0) {
            printf("文件关闭失败\n");
        }
        return head;
    }
        //文件非空则将指针移回原位
    else {
        rewind(fp);
    }
    //读取文件，创建链表
    while (!feof(fp)) {
        //创建结点
        Drink* temp = (Drink*)malloc(sizeof(Drink));
        if (!temp) {
            printf("内存分配失败");
            return NULL;
        }
        else {
            fscanf(fp, "%s", temp->ID);//酒水编号
            fscanf(fp, "%s", temp->brand);//酒水品牌
            fscanf(fp, "%s", temp->taste);//酒水口味
            fscanf(fp, "%d", &temp->package);//包装种类
            fscanf(fp, "%s", temp->single_bottle_capacity);//单瓶容量
            fscanf(fp, "%s", temp->single_box_quantity);//单箱数量
            fscanf(fp, "%f", &temp->restocking_price);//进货价格
            fscanf(fp, "%f", &temp->sale_price);//销售价格
            fscanf(fp, "%d", &temp->stock_quantity);//库存数量
            fscanf(fp, "%d", &temp->activity.form); //优惠形式
            fscanf(fp, "%f", &temp->activity.specific_1);//具体折扣
            for (int i = 0; i < 2; i++) {//具体赠品
                fscanf(fp, "%d", &temp->activity.specific_2[i]);
            }
            fscanf(fp, "%s", temp->activity.reason);//优惠原因
            for (int i = 0; i < 2; i++) {//活动时间
                fscanf(fp, "%s", temp->activity.date[i]);
            }
            temp->next = NULL;
            //加入链表
            tail->next = temp;
            tail = temp;
        }
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
    //删除最后一个冗余结点
    Drink* p = head;
    while (p->next != tail) {
        p = p->next;
    }
    p->next = NULL;
    free(tail);
    tail = NULL;
    //返回头结点
    return head;
}
//创建批发记录链表
WholesaleRecord* CreatWholesaleRecordList() {
    /*创建哨兵结点*/
    WholesaleRecord* head = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
    WholesaleRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    /*打开批发记录文件*/
    FILE* fp;
    /*若打开失败，则返回*/
    if ((fp = fopen("wholesale_records.txt", "a+")) == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }
    /*若打开成功，则读取文件，创建批发记录链表*/
    //检测是否空文件
    getc(fp);
    //空文件则关闭文件并返回
    if (feof(fp)) {
        if (fclose(fp) != 0) {
            printf("文件关闭失败\n");
        }
        return head;
    }
        //文件非空则将指针移回原位
    else {
        rewind(fp);
    }
    //读取文件，创建链表
    while (!feof(fp)) {
        //创建结点
        WholesaleRecord* temp = (WholesaleRecord*)malloc(sizeof(WholesaleRecord));
        if (!temp) {
            printf("内存分配失败\n");
            return NULL;
        }
        else {
            fscanf(fp, "%s", temp->order_number);//订单编号
            fscanf(fp, "%s", temp->date);//订单日期
            fscanf(fp, "%s", temp->user_ID);//客户账号
            fscanf(fp, "%s", temp->past_drink.ID);//酒水编号
            fscanf(fp, "%s", temp->past_drink.brand);//酒水品牌
            fscanf(fp, "%s", temp->past_drink.taste);//酒水口味
            fscanf(fp, "%d", &temp->past_drink.package);//包装种类
            fscanf(fp, "%s", temp->past_drink.single_bottle_capacity);//单瓶容量
            fscanf(fp, "%s", temp->past_drink.single_box_quantity);//单箱数量
            fscanf(fp, "%f", &temp->past_drink.sale_price);//销售价格
            fscanf(fp, "%d", &temp->goods_quantity); //批发数量
            //优惠
            for (int i = 0; i < 3; i++) {
                fscanf(fp, "%d", &temp->discount[i].form); //优惠形式
                fscanf(fp, "%f", &temp->discount[i].specific_1);//具体折扣
                for (int j = 0; j < 2; j++) {
                    fscanf(fp, "%d", &temp->discount[i].specific_2[j]);//具体赠品
                }
                fscanf(fp, "%s", temp->discount[i].reason);//优惠原因
            }
            fscanf(fp, "%d", &temp->goods_situation);//订单现况
            temp->next = NULL;
            //加入链表
            tail->next = temp;
            tail = temp;
        }
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
    //删除最后一个冗余结点
    WholesaleRecord* p = head;
    while (p->next != tail) {
        p = p->next;
    }
    p->next = NULL;
    free(tail);
    tail = NULL;
    //返回头结点
    return head;
}
//创建进货记录链表
PurchaseRecord* CreatPurchaseRecordList() {
    /*创建哨兵结点*/
    PurchaseRecord* head = (PurchaseRecord*)malloc(sizeof(PurchaseRecord));
    PurchaseRecord* tail = NULL;
    if (!head) {
        printf("内存分配失败");
        return NULL;
    }
    else {
        head->next = NULL;
        tail = head;
    }
    /*打开批进货记录文件*/
    FILE* fp;
    /*若打开失败，则返回*/
    if ((fp = fopen("purchase_records.txt", "a+")) == NULL) {
        printf("文件打开失败\n");
        return NULL;
    }
    /*若打开成功，则读取文件，创建进货记录链表*/
    //检测是否空文件
    getc(fp);
    //空文件则关闭文件并返回
    if (feof(fp)) {
        if (fclose(fp) != 0) {
            printf("文件关闭失败\n");
        }
        return head;
    }
        //文件非空则将指针移回原位
    else {
        rewind(fp);
    }
    //读取文件，创建链表
    while (!feof(fp)) {
        //创建结点
        PurchaseRecord* temp = (PurchaseRecord*)malloc(sizeof(PurchaseRecord));
        if (!temp) {
            printf("内存分配失败\n");
            return NULL;
        }
        else {
            fscanf(fp, "%s", temp->order_number);//订单编号
            fscanf(fp, "%s", temp->date);//订单日期
            fscanf(fp, "%s", temp->drink_ID);//酒水编号
            fscanf(fp, "%s", temp->brand);//酒水品牌
            fscanf(fp, "%s", temp->taste);//酒水口味
            fscanf(fp, "%d", &temp->package);//包装种类
            fscanf(fp, "%s", temp->single_bottle_capacity);//单瓶容量
            fscanf(fp, "%s", temp->single_box_quantity);//单箱数量
            fscanf(fp, "%f", &temp->restocking_price);//进货价格
            fscanf(fp, "%d", &temp->goods_quantity);//进货酒水数量
            temp->next = NULL;
            //加入链表
            tail->next = temp;
            tail = temp;
        }
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
    //删除最后一个冗余结点
    PurchaseRecord* p = head;
    while (p->next != tail) {
        p = p->next;
    }
    p->next = NULL;
    free(tail);
    tail = NULL;
    //返回头结点
    return head;
}

///更新文件
//更新管理员文件
void RenewManagerFile() {
    //打开管理员文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("manager.txt", "w+")) == NULL) {
        printf("管理员信息更新失败\n");
        return;
    }
    //若打开成功，则将管理员账号信息写入管理员文件
    if (manager) {
        fprintf(fp, "%s ", manager->ID);
        fprintf(fp, "%s ", manager->password);
        fprintf(fp, "%s ", manager->Tel);
        fprintf(fp, "%.2f", manager->fund);
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("管理员文件关闭失败\n");
    }
}
//更新用户文件
void RenewUserFile() {
    //打开用户文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("users.txt", "w+")) == NULL) {
        printf("文件打开失败\n");
        return;
    }
    //若打开成功，则将用户链表中的信息写入用户文件
    User* p = user_head->next;
    while (p) {
        fprintf(fp, "%s ", p->ID);//客户账号
        fprintf(fp, "%s ", p->password);//客户密码
        fprintf(fp, "%s ", p->name);//营业网点名称
        fprintf(fp, "%d ", p->level);//客户级别
        fprintf(fp, "%s ", p->address);//客户地址
        fprintf(fp, "%s ", p->Tel);//客户联系方式
        fprintf(fp, "%.2f ", p->total_funding);//账户余额
        fprintf(fp, "%.2f\n", p->total_consumption);//总消费
        p = p->next;
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
}
//更新酒水文件
void RenewDrinkFile() {
    //打开酒水文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("drink.txt", "w+")) == NULL) {
        printf("文件打开失败\n");
        return;
    }
    //若打开成功，则将酒水链表信息写入酒水文件
    Drink* p = drink_head->next;
    while (p) {
        fprintf(fp, "%s ", p->ID);//酒水编号
        fprintf(fp, "%s ", p->brand);//酒水品牌
        fprintf(fp, "%s ", p->taste);//酒水口味
        fprintf(fp, "%d ", p->package);//包装种类
        fprintf(fp, "%s ", p->single_bottle_capacity);//单瓶容量
        fprintf(fp, "%s ", p->single_box_quantity);//单箱数量
        fprintf(fp, "%.2f ", p->restocking_price);//进货价格
        fprintf(fp, "%.2f ", p->sale_price);//销售价格
        fprintf(fp, "%d ", p->stock_quantity);//库存数量
        fprintf(fp, "%d ", p->activity.form); //优惠形式
        fprintf(fp, "%.2f ", p->activity.specific_1);//具体折扣
        for (int i = 0; i < 2; i++) {//具体赠品
            fprintf(fp, "%d ", p->activity.specific_2[i]);
        }
        fprintf(fp, "%s ", p->activity.reason);//优惠原因
        fprintf(fp, "%s ", p->activity.date[0]);//活动开始时间
        fprintf(fp, "%s\n", p->activity.date[1]);//活动结束时间
        p = p->next;
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
}
//更新批发记录文件
void RenewWholesaleRecordFile() {
    //打开批发记录文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("wholesale_records.txt", "w+")) == NULL) {
        printf("文件打开失败\n");
        return;
    }
    //若打开成功，则将批发记录链表信息写入批发记录文件
    WholesaleRecord* p = wholesaleRecord_head->next;
    while (p) {
        fprintf(fp, "%s ", p->order_number);//订单编号
        fprintf(fp, "%s ", p->date);//订单日期
        fprintf(fp, "%s ", p->user_ID);//客户账号
        fprintf(fp, "%s ", p->past_drink.ID);//酒水编号
        fprintf(fp, "%s ", p->past_drink.brand);//酒水品牌
        fprintf(fp, "%s ", p->past_drink.taste);//酒水口味
        fprintf(fp, "%d ", p->past_drink.package);//包装种类
        fprintf(fp, "%s ", p->past_drink.single_bottle_capacity);//单瓶容量
        fprintf(fp, "%s ", p->past_drink.single_box_quantity);//单箱数量
        fprintf(fp, "%.2f ", p->past_drink.sale_price);//销售价格
        fprintf(fp, "%d ", p->goods_quantity);//批发数量
        //优惠
        for (int i = 0; i < 3; i++) {
            fprintf(fp, "%d ", p->discount[i].form); //优惠形式
            fprintf(fp, "%.2f ", p->discount[i].specific_1);//具体折扣
            for (int j = 0; j < 2; j++) {
                fprintf(fp, "%d ", p->discount[i].specific_2[j]);//具体赠品
            }
            fprintf(fp, "%s ", p->discount[i].reason);//优惠原因
        }
        fprintf(fp, "%d\n", p->goods_situation);//订单现况
        p = p->next;
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
}
//更新进货记录文件
void RenewPurchaseRecordFile() {
    //打开批进货记录文件
    FILE* fp;
    //若打开失败，则返回
    if ((fp = fopen("purchase_records.txt", "w+")) == NULL) {
        printf("文件打开失败\n");
        return;
    }
    //若打开成功，则进货记录链表信息写入进货记录文件
    PurchaseRecord* p = purchaseRecord_head->next;
    while (p) {
        fprintf(fp, "%s ", p->order_number);//订单编号
        fprintf(fp, "%s ", p->date);//进货日期
        fprintf(fp, "%s ", p->drink_ID);//酒水编号
        fprintf(fp, "%s ", p->brand);//酒水品牌
        fprintf(fp, "%s ", p->taste);//酒水口味
        fprintf(fp, "%d ", p->package);//包装种类
        fprintf(fp, "%s ", p->single_bottle_capacity);//单瓶容量
        fprintf(fp, "%s ", p->single_box_quantity);//单箱数量
        fprintf(fp, "%.2f ", p->restocking_price);//进货价格
        fprintf(fp, "%d\n", p->goods_quantity);//进货酒水数量
        p = p->next;
    }
    //关闭文件
    if (fclose(fp) != 0) {
        printf("文件关闭失败\n");
    }
}

///检验信息
//检验输入信息是否正确
bool isInputCorrect(char* correct_string, char* input) {
    if (strlen(input) != strlen(correct_string)) { return false; }
    for (int i = 0; input[i] != '\0' && correct_string[i] != '\0'; i++) {
        if (input[i] != correct_string[i]) { return false; }
    }
    return true;
}
//检验密码是否符合规范
bool isPasswordAllowed(char* password) {
    int capitalization_flag = 0;
    int lowercase_flag = 0;
    int num_flag = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (password[i] < 33 || password[i] > 127) { return false; }
        else if (password[i] >= 'A' && password[i] <= 'Z') { capitalization_flag = 1; }
        else if (password[i] >= 'a' && password[i] <= 'z') { lowercase_flag = 1; }
        else if (password[i] >= '0' && password[i] <= '9') { num_flag = 1; }
    }
    if (strlen(password) < 10 || strlen(password) > 20) { return false; }
    else if (!capitalization_flag || !lowercase_flag || !num_flag) { return false; }
    else { return true; }
}
//检验数字串（联系方式或金额）是否符合规范
bool isNumberAllowed(char* number) {
    for (int i = 0; number[i] != '\0'; i++) {
        if (i == 0 && number[i] == '0') { return false; }
        if (number[i] < '0' || number[i] > '9') { return false; }
    }
    return true;
}
//检验字符串（地址或名称）是否符合规范
bool isStringAllowed(char* string) {
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') { return false; }
    }
    return true;
}
//检验时间格式是否正确
bool isTimeAllowed(char* time) {
    if (strlen(time) != 19) { return false; }
    for (int i = 0; i < 19; i++) {
        if (i == 4 || i == 7) {
            if (time[i] != '-') { return false; }
        }
        else if (i == 10) {
            if (time[i] != '_') { return false; }
        }
        else if (i == 13 || i == 16) {
            if (time[i] != ':') { return false; }
        }
        else {
            if (time[i] < '0' || time[i] > '9') { return false; }
        }
    }
    //月
    char month[3] = { "" };
    month[0] = time[5];
    month[1] = time[6];
    month[2] = '\0';
    if (atoi(month) < 1 || atoi(month) > 12) { return false; }
    //日
    char day[3] = { "" };
    day[0] = time[8];
    day[1] = time[9];
    day[2] = '\0';
    if (atoi(day) < 1) { return false; }
    if (atoi(month) == 2 && atoi(day) > 29) { return false; }
    if (atoi(month) % 2) {
        if (atoi(month) < 7 && atoi(day) > 30) { return false; }
        if (atoi(month) > 7 && atoi(day) > 31) { return false; }
    }
    else {
        if (atoi(month) < 7 && atoi(day) > 31) { return false; }
        if (atoi(month) > 7 && atoi(day) > 30) { return false; }
    }
    //时
    char hour[3] = { "" };
    hour[0] = time[11];
    hour[1] = time[12];
    hour[2] = '\0';
    if (atoi(hour) > 23) { return false; }
    //分
    char minute[3] = { "" };
    minute[0] = time[14];
    minute[1] = time[15];
    minute[2] = '\0';
    if (atoi(minute) > 59) { return false; }
    //秒
    char second[3] = { "" };
    second[0] = time[17];
    second[1] = time[18];
    second[2] = '\0';
    if (atoi(second) > 59) { return false; }
    return true;
}
//检验时间顺序是否正确
bool isChronological(char* early_time, char* late_time) {
    char early[5] = { "" };
    char late[5] = { "" };
    //年
    for (int i = 0; i < 4; i++) {
        early[i] = early_time[i];
        late[i] = late_time[i];
    }
    early[4] = '\0';
    late[4] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    //月
    for (int i = 0; i < 2; i++) {
        early[i] = early_time[5 + i];
        late[i] = late_time[5 + i];
    }
    early[2] = '\0';
    late[2] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    //日
    for (int i = 0; i < 2; i++) {
        early[i] = early_time[8 + i];
        late[i] = late_time[8 + i];
    }
    early[2] = '\0';
    late[2] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    //时
    for (int i = 0; i < 2; i++) {
        early[i] = early_time[12 + i];
        late[i] = late_time[12 + i];
    }
    early[2] = '\0';
    late[2] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    //分
    for (int i = 0; i < 2; i++) {
        early[i] = early_time[15 + i];
        late[i] = late_time[15 + i];
    }
    early[2] = '\0';
    late[2] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    //秒
    for (int i = 0; i < 2; i++) {
        early[i] = early_time[18 + i];
        late[i] = late_time[18 + i];
    }
    early[2] = '\0';
    late[2] = '\0';
    if (atoi(early) < atoi(late)) { return true; }
    else if (atoi(early) > atoi(late)) { return false; }
    else { return true; }
}
//模糊查找
bool isInclude(char* string, char* input) {
    int start = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        int flag = 0;
        for (int j = start; string[j] != '\0'; j++) {
            if (input[i] == string[j]) {
                flag = 1;
                start = j + 1;
                break;
            }
        }
        if (!flag) { return false; }
    }
    return true;
}
//用户是否存在
User* isUserExist(char* input) {
    User* user = user_head->next;
    while (user) {
        if (isInputCorrect(user->ID, input) || isInputCorrect(user->Tel, input)) { break; }
        user = user->next;
    }
    return user;
}
//酒水是否存在（返回前驱结点）
Drink* isDrinkExist(char* drink_ID) {
    Drink* drink = drink_head;
    while (drink->next) {
        if (isInputCorrect(drink->next->ID, drink_ID)) { break; }
        drink = drink->next;
    }
    return drink;
}
//检测订单是否存在（返回前驱结点）
WholesaleRecord* isOrderExist() {
    printf("请输入订单编号(输入0返回)：");
    char order_number[MaxSize] = { "" };
    fgets(order_number, sizeof(order_number), stdin);
    //检验是否返回
    if (order_number[0] == '0' && strlen(order_number) == 2) { return NULL; }
    //查找订单
    WholesaleRecord* wholesale_record = wholesaleRecord_head;
    while (wholesale_record->next) {
        if (isInputCorrect(wholesale_record->next->order_number, order_number)) { break; }
        wholesale_record = wholesale_record->next;
    }
    return wholesale_record;
}
//生成编号
char* BuildID(char* pre_ID) {
    char ID[MaxSize] = { "" };
    int nums = atoi(pre_ID);
    nums++;
    int len = strlen(pre_ID);
    for (int i = len - 1; i >= 0; i--) {
        ID[i] = (nums % 10 + '0');
        nums /= 10;
    }
    ID[len] = '\0';
    return ID;
}
///输入信息
//输入订单现状
int isSituationCorrect(char* situation) {
    fgets(situation, sizeof(situation), stdin);
    if (situation[0] == '0' && strlen(situation) == 2) { return 0; }
    else if (situation[0] == '1' && strlen(situation) == 2) { return 1; }
    else if (situation[0] == '2' && strlen(situation) == 2) { return 1; }
    else if (situation[0] == '3' && strlen(situation) == 2) { return 1; }
    else if (situation[0] == '4' && strlen(situation) == 2) { return 1; }
    else if (situation[0] == '5' && strlen(situation) == 2) { return 1; }
    else if (situation[0] == '6' && strlen(situation) == 2) { return 1; }
    else {
        printf("非法选择，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入品牌
int isBrandCorrect(char* brand) {
    fgets(brand, sizeof(brand), stdin);
    if (brand[0] == '0' && strlen(brand) == 2) { return 0; }
    if (strlen(brand) && strlen(brand) < 21 && isStringAllowed(brand)) { return 1; }
    else {
        printf("酒水品牌错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入口味
int isTasteCorrect(char* taste) {
    fgets(taste, sizeof(taste), stdin);
    if (taste[0] == '0' && strlen(taste) == 2) { return 0; }
    if (strlen(taste) && strlen(taste) < 21 && isStringAllowed(taste)) { return 1; }
    else {
        printf("请输入酒水口味！\n");
        system("read");
        return 2;
    }
}
//输入包装(搜索type=1)
int isPackageCorrect(char* package, int type) {
    fgets(package, sizeof(package), stdin);
    if (package[0] == '0' && strlen(package) == 2) { return 0; }
    else if (package[0] == '1' && strlen(package) == 2) { return 1; }
    else if (package[0] == '2' && strlen(package) == 2) { return 1; }
    else if (package[0] == '3' && strlen(package) == 2) { return 1; }
    else if (type && package[0] == '4' && strlen(package) == 2) { return 1; }
    else {
        printf("非法选择，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入单瓶容量
int isSingleBottleCapacityCorrect(char* single_bottle_capacity) {
    fgets(single_bottle_capacity, sizeof(single_bottle_capacity), stdin);
    if (single_bottle_capacity[0] == '0' && strlen(single_bottle_capacity) == 2) { return 0; }
    if (strlen(single_bottle_capacity) && strlen(single_bottle_capacity) < 6 && isNumberAllowed(single_bottle_capacity)) { return 1; }
    else {
        printf("单瓶容量错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入单箱数量
int isSingleBoxQuantityCorrect(char* single_box_quantity) {
    fgets(single_box_quantity, sizeof(single_box_quantity), stdin);
    if (single_box_quantity[0] == '0' && strlen(single_box_quantity) == 2) { return 0; }
    if (strlen(single_box_quantity) && strlen(single_box_quantity) < 6 && isNumberAllowed(single_box_quantity)) { return 1; }
    else {
        printf("单箱数量错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入价格
int isPriceCorrect(char* price) {
    fgets(price, sizeof(price), stdin);
    if (price[0] == '0' && strlen(price) == 2) { return 0; }
    if (strlen(price) && strlen(price) < 6 && isNumberAllowed(price)) { return 1; }
    else {
        printf("价格错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入箱数
int isGoodsQuantityCorrect(char* goods_quantity) {
    fgets(goods_quantity, sizeof(goods_quantity), stdin);
    if (goods_quantity[0] == '0' && strlen(goods_quantity) == 2) { return 0; }
    if (strlen(goods_quantity) && strlen(goods_quantity) < 6 && isNumberAllowed(goods_quantity)) { return 1; }
    else {
        printf("数量错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入折扣
int isDiscountCorrect(char* discount) {
    fgets(discount, sizeof(discount), stdin);
    if (discount[0] == '0' && strlen(discount) == 2) { return 0; }
    int flag = 0;
    if (strlen(discount) != 4) { flag = 1; }
    if (discount[0] != '0') { flag = 1; }
    if (discount[1] != '.') { flag = 1; }
    if (discount[2] < '0' || discount[0] > '9') { flag = 1; }
    if (discount[3] < '0' || discount[0] > '9') { flag = 1; }
    if (discount[4] != '\0') { flag = 1; }
    if (!flag) { return 1; }
    else {
        printf("折扣错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//输入活动原因
int isReasonCorrect(char* reason) {
    fgets(reason, sizeof(reason), stdin);
    if (reason[0] == '0' && strlen(reason) == 2) { return 0; }
    else if (strlen(reason) && strlen(reason) < 51 && isStringAllowed(reason)) { return 1; }
    else {
        printf("活动原因输入错误，请重新输入！\n");
        system("read");
        return 2;
    }
}
//确认输入
int isSure() {
    char select[MaxSize] = { "" };
    fgets(select, sizeof(select), stdin);
    if (select[0] == '1' && strlen(select) == 2) { return 0; }
    else if (select[0] == '2' && strlen(select) == 2) { return 1; }
    else {
        printf("非法选择，请重新输入！\n");
        system("read");
        return 2;
    }
}