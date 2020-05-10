#include "mbed.h"
#include "mbed_rpc.h"

/**
 *  This example program has been updated to use the RPC implementation in the new mbed libraries.
 *  This example demonstrates using RPC over serial
**/
RpcDigitalOut myled1(LED1,"myled1");
RpcDigitalOut myled2(LED2,"myled2");
RpcDigitalOut myled3(LED3,"myled3");
Serial pc(USBTX, USBRX);
void LEDBlink(Arguments *in, Reply *out);
RPCFunction rpcLED(&LEDBlink, "LEDBlink");
double x, y;

int main() {
    //The mbed RPC classes are now wrapped to create an RPC enabled version - see RpcClasses.h so don't add to base class

    // receive commands, and send back the responses
    char buf[256], outbuf[256];
    sprintf(buf, "/myled1/write 1");
    RPC::call(buf, outbuf);
    sprintf(buf, "/myled2/write 1");
    RPC::call(buf, outbuf);
    sprintf(buf, "/myled3/write 1");
    RPC::call(buf, outbuf);

    while(1) {
        memset(buf, 0, 256);
        for (int i = 0; ; i++) {
            char recv = pc.getc();
            if (recv == '\r') {
                pc.printf("\r\n");
                break;
            }
            buf[i] = pc.putc(recv);
        }
        
        //Call the static call method on the RPC class
        RPC::call(buf, outbuf);
        pc.printf("%s\r\n", outbuf);
    }
}

// Make sure the method takes in Arguments and Reply objects.
void LEDBlink (Arguments *in, Reply *out)   {
    bool success = true;

    // In this scenario, when using RPC delimit the two arguments with a space.
    x = in->getArg<double>();

    // Have code here to call another RPC function to wake up specific led or close it.
    char buffer[200], outbuf[256];
    char strings[20];
    int led = x;
    
    int n = sprintf(strings, "/myled%d/write 0", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
    wait(0.5);
    n = sprintf(strings, "/myled%d/write 1", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
    wait(0.5);
    n = sprintf(strings, "/myled%d/write 0", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
    wait(0.5);
    n = sprintf(strings, "/myled%d/write 1", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
    wait(0.5);
    n = sprintf(strings, "/myled%d/write 0", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
    wait(0.5);
    n = sprintf(strings, "/myled%d/write 1", led);
    strcpy(buffer, strings);
    RPC::call(buffer, outbuf);
    if (success) {
        out->putData(buffer);
    } else {
        out->putData("Failed to execute LED blink.");
    }
}

