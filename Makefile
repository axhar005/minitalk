# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:34:33 by oboucher          #+#    #+#              #
#    Updated: 2023/04/13 21:35:42 by oboucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- LIBRARY NAME ---#
NAMES = server
NAMEC = client

CNAME = $(YELLOW)~ Minitalk

#--- COMMAND VARIABLES ---#
CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

RM = rm -f

AR = ar rcs

MK = mkdir -p

#--- COLORS ---#
GREEN	=	\033[1;32m

RED		=	\033[1;31m

BLUE	=	\033[1;34m

YELLOW	=	\033[1;93m

WHITE	=	\033[1;97m

RESET 	= 	\033[0m

#--- ECHO COLOR ---#
RECHO = @echo "$(RED)"

WECHO = @echo "$(WHITE)"

#--- INCLUDE ---#
INCDIR = inc

#--- SOURCE ---#
SRCDIR = src

SRC = 	ft_atoi.c ft_bzero.c ft_calloc.c ft_isdegit.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c ft_sfree.c minitalk_utilities.c
SRCS = 	server.c
SRCC = 	client.c

VPATH	=	${SRCDIR}

#--- OBJECT ---#
OBJDIR  =   obj

OBJ = $(addprefix ${OBJDIR}/, ${SRC:.c=.o})
OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})
OBJC = $(addprefix ${OBJDIR}/, ${SRCC:.c=.o})

#--- RULES ---#
${OBJDIR}/%.o : %.c
	@${CC} ${CFLAGS} -I${INCDIR} -I. -c $< -o $@
	
all				: 	 	pokeball $(NAMES) $(NAMEC)
	
$(NAMES)			: 		$(OBJDIR) $(OBJ) $(OBJS)
	@${CC} ${CFLAGS} -I${INCDIR} -o ${NAMES} ${OBJ} ${OBJS}
	
	
${NAMEC}			:		$(OBJDIR) $(OBJ) $(OBJC)
	@${CC} ${CFLAGS} -I${INCDIR} -o ${NAMEC} ${OBJ} ${OBJC}
	@echo "$(CNAME)${GREEN} sucessefully compiled 📁.${RESET}"

$(OBJDIR)		:
	@$(MK) ${OBJDIR}


pokeball		:
	clear
	$(RECHO)"              ######              "
	@echo	"           ############           "
	@echo	"          ##############          "
	@echo	"         #######  #######         "
	$(WECHO)"         #######  #######         "
	@echo	"          ##############          "
	@echo	"           ############           "
	@echo	"              ######              \n"
	@echo	"${BLUE}----------------------------------------\n"
	@echo	"|               ${YELLOW}MINITALK${BLUE}               |\n"
	@echo	"----------------------------------------\n${RESET}"

run				:		all
	@./${NAMES}


clean			:
	@$(RM) $(OBJ)
	@$(RM) $(OBJC)
	@$(RM) $(OBJS)
	@$(RM)r $(OBJDIR)
	
fclean			: 		clean	
	@$(RM) $(NAMES)
	@$(RM) $(NAMEC)
	@echo "$(CNAME)${GREEN} object files and executable successfully removed 🗑.${RESET}"

re				: 		fclean all

.PHONY			: 		all clean fclean re