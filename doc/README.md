cpp file for testing the lex:
```
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
```
lex output:
```
# LOG-> int
token       0  at line      4  is                          <1, >    should be: int
# LOG-> main
token       1  at line      4  is                      <0, main>    should be: main
# LOG-> (
token       2  at line      4  is                         <42, >    should be: (
# LOG-> void
token       3  at line      4  is                         <12, >    should be: void
# LOG-> )
token       4  at line      4  is                         <43, >    should be: )
# LOG-> {
token       5  at line      4  is                         <46, >    should be: {
# LOG-> int
token       6  at line      6  is                          <1, >    should be: int
# LOG-> a
token       7  at line      6  is                         <0, a>    should be: a
# LOG-> =
token       8  at line      6  is                         <28, >    should be: =
# LOG-> 1
token       9  at line      6  is                       <100, 1>    should be: 1
# LOG-> ;
token      10  at line      6  is                         <48, >    should be: ;
# LOG-> int
token      11  at line      7  is                          <1, >    should be: int
# LOG-> b
token      12  at line      7  is                         <0, b>    should be: b
# LOG-> =
token      13  at line      7  is                         <28, >    should be: =
# LOG-> 2
token      14  at line      7  is                       <100, 2>    should be: 2
# LOG-> ;
token      15  at line      7  is                         <48, >    should be: ;
# LOG-> if
token      16  at line      8  is                         <16, >    should be: if
# LOG-> (
token      17  at line      8  is                         <42, >    should be: (
# LOG-> a
token      18  at line      8  is                         <0, a>    should be: a
# LOG-> ==
token      19  at line      8  is                         <22, >    should be: ==
# LOG-> 1
token      20  at line      8  is                       <100, 1>    should be: 1
# LOG-> &&
token      21  at line      8  is                         <35, >    should be: &&
# LOG-> b
token      22  at line      8  is                         <0, b>    should be: b
# LOG-> ==
token      23  at line      8  is                         <22, >    should be: ==
# LOG-> 2
token      24  at line      8  is                       <100, 2>    should be: 2
# LOG-> ||
token      25  at line      8  is                         <36, >    should be: ||
# LOG-> (
token      26  at line      8  is                         <42, >    should be: (
# LOG-> a
token      27  at line      8  is                         <0, a>    should be: a
# LOG-> !
token      28  at line      8  is                         <33, >    should be: !
# LOG-> =
token      29  at line      8  is                         <28, >    should be: =
# LOG-> 2
token      30  at line      8  is                       <100, 2>    should be: 2
# LOG-> ||
token      31  at line      8  is                         <36, >    should be: ||
# LOG-> b
token      32  at line      8  is                         <0, b>    should be: b
# LOG-> !
token      33  at line      8  is                         <33, >    should be: !
# LOG-> =
token      34  at line      8  is                         <28, >    should be: =
# LOG-> 3
token      35  at line      8  is                       <100, 3>    should be: 3
# LOG-> )
token      36  at line      8  is                         <43, >    should be: )
# LOG-> )
token      37  at line      8  is                         <43, >    should be: )
# LOG-> {
token      38  at line      8  is                         <46, >    should be: {
# LOG-> while
token      39  at line      9  is                         <15, >    should be: while
# LOG-> (
token      40  at line      9  is                         <42, >    should be: (
# LOG-> 1
token      41  at line      9  is                       <100, 1>    should be: 1
# LOG-> )
token      42  at line      9  is                         <43, >    should be: )
# LOG-> {
token      43  at line      9  is                         <46, >    should be: {
# LOG-> int
token      44  at line     10  is                          <1, >    should be: int
# LOG-> c
token      45  at line     10  is                         <0, c>    should be: c
# LOG-> =
token      46  at line     10  is                         <28, >    should be: =
# LOG-> a
token      47  at line     10  is                         <0, a>    should be: a
# LOG-> +
token      48  at line     10  is                         <29, >    should be: +
# LOG-> b
token      49  at line     10  is                         <0, b>    should be: b
# LOG-> -
token      50  at line     10  is                         <31, >    should be: -
# LOG-> b
token      51  at line     10  is                         <0, b>    should be: b
# LOG-> -
token      52  at line     10  is                         <31, >    should be: -
# LOG-> a
token      53  at line     10  is                         <0, a>    should be: a
# LOG-> ;
token      54  at line     10  is                         <48, >    should be: ;
# LOG-> switch
token      55  at line     11  is                          <6, >    should be: switch
# LOG-> (
token      56  at line     11  is                         <42, >    should be: (
# LOG-> a
token      57  at line     11  is                         <0, a>    should be: a
# LOG-> )
token      58  at line     11  is                         <43, >    should be: )
# LOG-> {
token      59  at line     11  is                         <46, >    should be: {
# LOG-> case
token      60  at line     12  is                          <7, >    should be: case
# LOG-> 1
token      61  at line     12  is                       <100, 1>    should be: 1
# LOG-> :
token      62  at line     12  is                         <0, :>    should be: :
# LOG-> break
token      63  at line     12  is                          <9, >    should be: break
# LOG-> ;
token      64  at line     12  is                         <48, >    should be: ;
# LOG-> default
token      65  at line     13  is                          <8, >    should be: default
# LOG-> :
token      66  at line     13  is                         <0, :>    should be: :
# LOG-> a
token      67  at line     13  is                         <0, a>    should be: a
# LOG-> =
token      68  at line     13  is                         <28, >    should be: =
# LOG-> 2
token      69  at line     13  is                       <100, 2>    should be: 2
# LOG-> ;
token      70  at line     13  is                         <48, >    should be: ;
# LOG-> }
token      71  at line     14  is                         <47, >    should be: }
# LOG-> }
token      72  at line     15  is                         <47, >    should be: }
# LOG-> }
token      73  at line     16  is                         <47, >    should be: }
# LOG-> return
token      74  at line     17  is                         <11, >    should be: return
# LOG-> 0
token      75  at line     17  is                       <100, 0>    should be: 0
# LOG-> ;
token      76  at line     17  is                         <48, >    should be: ;
# LOG-> }
token      77  at line     18  is                         <47, >    should be: }
```
