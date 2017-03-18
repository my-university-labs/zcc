/* author: dongchangzhang */
/* time: Sat 18 Mar 2017 02:20:57 PM CST */

int main(void) {
    // this is a test fo my lex
    int a=1;
    int b=2;
    if(a==1&&b==2||(a!=2||b!=3)){
        while(1){
            int c=a+b-b-a;
            switch(a) {
                case 1: break;
                default: a=2;
            }
        }
    }
    return 0;
}
