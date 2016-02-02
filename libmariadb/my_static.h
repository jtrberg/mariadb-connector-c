/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA 02111-1307, USA */

/*
  Static variables for mysys library. All definied here for easy making of
  a shared library
*/

#include "mysys_priv.h"
#include <signal.h>

#define MAX_SIGNALS	10		/* Max signals under a dont-allow */
#define MIN_KEYBLOCK	(min(IO_SIZE,1024))
#define MAX_KEYBLOCK	8192		/* Max keyblocklength == 8*IO_SIZE */
#define MAX_BLOCK_TYPES MAX_KEYBLOCK/MIN_KEYBLOCK

struct st_remember {
  int number;
  sig_handler (*func)(int number);
};

struct irem {
    struct remember *_pNext;		/* Linked list of structures	   */
    struct remember *_pPrev;		/* Other link			   */
    my_string _sFileName;		/* File in which memory was new'ed */
    uint _uLineNum;			/* Line number in above file	   */
    uint _uDataSize;			/* Size requested		   */
    long _lSpecialValue;		/* Underrun marker value	   */
};

struct remember {
    struct irem tInt;
    char aData[1];
};

extern char	NEAR ma_cur_dir[FN_REFLEN],NEAR ma_ma_ma_ma_ma_ma_home_dir_buff[FN_REFLEN];

extern volatile int _ma_signals;
extern struct st_remember _ma_sig_remember[MAX_SIGNALS];

extern const char *ma_soundex_map;

extern MA_USED_MEM* ma_once_root_block;
extern uint	 ma_once_extra;

#if !defined(HAVE_TEMPNAM) || defined(HPUX11)
extern int	_my_tempnam_used;
#endif

extern uint	cNewCount;
extern struct remember *pRememberRoot;

#if defined(THREAD) && !defined(__WIN__)
extern sigset_t my_signals;		/* signals blocked by mf_brkhant */
#endif
