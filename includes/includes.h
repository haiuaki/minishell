/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:12:02 by juljin            #+#    #+#             */
/*   Updated: 2026/01/24 15:42:40 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

/* ----------------------- Standard C library headers ----------------------- */

# include <stdio.h>					// For printf() & perror()
# include <stdlib.h>				// For malloc(), free(), exit() & getenv()
# include <string.h>				// For strerror()
# include <errno.h>					// For errno

/* ----------------------------- POSIX headers ------------------------------ */

# include <dirent.h>				// For opendir(), readdir() & closedir()
# include <fcntl.h>					// For open(), O_RDONLY, O_WRONLY, etc.
# include <signal.h>				// For signal(), sigaction(), sigemptyset(),
									// sigaddset() & kill()
# include <sys/ioctl.h>				// For ioctl()
# include <sys/resource.h>			// For rusage structure (wait3/4())
# include <sys/stat.h>				// For stat(), lstat() & fstat()
# include <sys/time.h>				// For timeval structure (wait3/4())
# include <sys/types.h>				// For pid_t & DIR types
# include <sys/wait.h>				// For wait(), waitpid(), wait3() & wait4()
# include <termios.h>				// For termios structure, tcsetattr()
									// & tcgetattr()
# include <unistd.h>				// For write(), read(), close(), access(),
									// fork(), getcwd(), chdir(), unlink(),
									// execve(), dup(), dup2(), pipe(),
									// isatty(), ttyname() & ttyslot()

/* ------------------------ Terminal control headers ------------------------ */

# include <curses.h>				// For terminal capabilities
# include <term.h>					// For tgetent(), tgetflag(), tgetnum(),
									// tgetstr(), tgoto() & tputs()

/* ------------------------ Readline library headers ------------------------ */

# include <readline/readline.h>		// For readline(), rl_clear_history(),
									// rl_on_new_line(), rl_replace_line()
									// & rl_redisplay()
# include <readline/history.h>		// For add_history()

#endif