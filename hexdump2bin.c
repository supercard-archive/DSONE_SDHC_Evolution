#include <stdio.h>

static void dehex(unsigned char *buf) {
	static const unsigned char hextab[] = {
		['0'] = 0,
		['1'] = 1,
		['2'] = 2,
		['3'] = 3,
		['4'] = 4,
		['5'] = 5,
		['6'] = 6,
		['7'] = 7,
		['8'] = 8,
		['9'] = 9,
		['a'] = 0xa,
		['b'] = 0xb,
		['c'] = 0xc,
		['d'] = 0xd,
		['e'] = 0xe,
		['f'] = 0xf,
	};
	unsigned char* p = buf, c = 0;
	unsigned long odd = 0;
	while(1) {
		switch(*p) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			if(odd++ & 1) {
				c = (c << 4) | hextab[*p];
				fputc(c, stdout);
			} else
				c = hextab[*p];
			break;
		default: return;
		}
		++p;
	}
}

static int usage() {
	fprintf(stderr,
		"usage: hexdump2bin FILE\n"
		"\n converts hexdump to binary (output to stdout)\n"
	);
	return 1;
}

int main(int argc, char** argv) {
	if(argc != 2) return usage();
	FILE *f = (argv[1][0] == '-' && !argv[1][1]) ? stdin: fopen(argv[1], "r");
	if(!f) {
		fprintf(stderr, "error opening file: %m\n");
		return 1;
	}
	char buf[1024];
	while(fgets(buf, sizeof buf, f)) {
		dehex(buf);
	}
	fclose(f);
	return 0;
}
