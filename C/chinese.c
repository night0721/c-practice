#include <io.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	wprintf(L"你好!\n");
}