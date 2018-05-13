#include "headers/project.h"

unsigned int text_file_dump(char *fn)
{
	bpb_t *bpb=(bpb_t*)&_end;
	fatdir_t *dir=(fatdir_t*)(&_end+512);
	unsigned int root_sec, s;
	// find the root directory's LBA
	root_sec=((bpb->spf16?bpb->spf16:bpb->spf32)*bpb->nf)+bpb->rsc;
	//WARNING gcc generates bad code for bpb->nr, causing unaligned exception
	s=*((unsigned int*)&bpb->nf);
	s>>=8;
	s&=0xFFFF;
	s<<=5;
	// now s=bpb->nr*sizeof(fatdir_t));
	if(bpb->spf16==0) {
		// adjust for FAT32
		root_sec+=(bpb->rc-2)*bpb->spc;
	}
	// add partition LBA
	root_sec+=partitionlba;
	// load the root directory
	if(sd_readblock(root_sec,(unsigned char*)dir,s/512+1)) {
		// iterate on each entry and check if it's the one we're looking for
		for(;dir->name[0]!=0;dir++) {
			// is it a valid entry?
			if(dir->name[0]==0xE5 || dir->attr[0]==0xF) continue;
			// filename match?
			if(!__builtin_memcmp(dir->name,fn,11)) {
				uart_puts("FAT File ");
				uart_puts(fn);
				uart_puts(" starts at cluster: ");
				uart_hex(((unsigned int)dir->ch)<<16|dir->cl);
				uart_puts("\n");
				// if so, return starting cluster
		if(((unsigned int) dir->ch)<<16|dir->cl)
		{	
			if(dir->size > 0) lfb_print(0, 1, "size > 0");
					char buffer[512];
			itoa(dir->size, buffer);
			lfb_print(0, 0, &buffer[0]);
			unsigned int size = dir->size;
			void *ptr = fat_readfile(((unsigned int)dir->ch)<<16|dir->cl);
			unsigned long a, temp;
				unsigned int x = 0, y = 0;
				unsigned char c;
			a = (unsigned long)ptr;
				for(unsigned int bytes_copied = 0; bytes_copied < size; bytes_copied++)
				{
						c=*((unsigned char *)(a));
						temp = (c<32||c>127?'.':c);
						if(c == '\n')
						{
								y++;
								x = 0;
								//lfb_print(x, y, (char *)&temp);
						}
						else if(c != '\r')
						{
								lfb_print(x, y, (char *)&temp);
								x++;
						}
				else
				{
					x = 0;
				}
				a++;
			}
		}
		return 0;

			}
		}
		uart_puts("ERROR: file not found\n");
	} else {
		uart_puts("ERROR: Unable to load root directory\n");
	}
	return 0;
}