#include "test.h"
extern PlayerCc::PlayerClient *robot;
Test::Test()
{
}
void Test::run()
{
zmienna = 10;

for(int i = 0; i<100; i++)
{

    zmienna += 1;
    sleep(1);


}
}

void testt(){

    robot->Read();

}
