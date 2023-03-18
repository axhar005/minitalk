# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:34:33 by oboucher          #+#    #+#              #
#    Updated: 2023/03/17 20:00:51 by oboucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- LIBRARY NAME ---#
NAME = minitalk

CNAME = $(YELLOW)~ Minitalk

#--- COMMAND VARIABLES ---#
CC = gcc

CFLAGS = -Wall -Wextra -Werror

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

SRCS = 	client.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isdegit.c ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strlen.c server.c

VPATH	=	${SRCDIR}

#--- OBJECT ---#
OBJDIR  =   obj

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

#--- RULES ---#
${OBJDIR}/%.o : %.c
	@${CC} ${CFLAGS} -I${INCDIR} -I. -c $< -o $@
	
all				: 	 	pokeball $(NAME)
	
$(NAME)			: 		$(OBJDIR) $(OBJS)
	@${CC} ${CFLAGS} -I${INCDIR} -o ${NAME} ${OBJS}
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
	@echo	"${BLUE}----------------------------------\n"
	@echo	"|            ${YELLOW}MINITALK${BLUE}            |\n"
	@echo	"----------------------------------\n${RESET}"

run 			:		all
	@./${NAME}
	
clean			:
	@$(RM) $(OBJS)
	@$(RM)r $(OBJDIR)
	
fclean			: 		clean	
	@$(RM) $(NAME)
	@echo "$(CNAME)${GREEN} object files and executable successfully removed 🗑.${RESET}"

re				: 		fclean all

.PHONY			: 		all clean fclean re