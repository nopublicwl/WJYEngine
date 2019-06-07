/*
 * TWJYEngineLinuxH.h
 *
 *  Created on: 2009-6-24
 *      Author: root
 */
	#if WJYOperat_System != WJYOperatSystem_Linux
		#define TWJYENGINELINUXH_H_
	#endif
#ifndef TWJYENGINELINUXH_H_
#define TWJYENGINELINUXH_H_

	#include <sys/time.h>
	#include <math.h>
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <iostream>
	#include <pthread.h>
	#include <dlfcn.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <sys/sysinfo.h>
//	#include <linux/unistd.h>
	#include <linux/kernel.h>
	#include <semaphore.h>
	#include <signal.h>
	#include <netinet/in.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/wait.h>
	#include <netinet/in.h>
	#include <sys/epoll.h>
	#include <sys/select.h>
//#include <linux/unistd.h>
//	#include <sys/sysinfo.h>
//	#ifdef __GNUC__
//		#include <ext/hash_map>
//		using   namespace	__gnu_cxx;
//	#else
//		#include <hash_map>
//	#endif
//	#include <vector>
//	#include <string>
//		#include <GL/glew.h>
//		#include <GL/glut.h>
//		#include <GL/glx.h>
//		#include <X11/Xlib.h>
//		#include <GL/glext.h>
//		#include <GL/gl.h>
//		#include <GL/glu.h>
	using namespace std;
	#define HASH_MAP hash_map
#endif /* TWJYENGINELINUXH_H_ */
