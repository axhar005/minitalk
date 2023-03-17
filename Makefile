# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oboucher <oboucher@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 12:34:33 by oboucher          #+#    #+#              #
#    Updated: 2023/03/16 15:34:23 by oboucher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#--- LIBRARY NAME ---#
NAME = 

CNAME = $(YELLOW)~ PRINTF ${GREEN}

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
LIBFT = libft.a

LDIR = ft_libft/

SRCDIR = src

SRCS = 	server.c client.c client.c ft_bzero.c ft_calloc.c ft_itoa.c ft_putendl_fd.c ft_putnbr_fd.c  ft_putstr_fd.c  ft_strlen.c server.c

VPATH	=	${SRCDIR}

#--- OBJECT ---#
OBJDIR  =   obj

OBJS = $(addprefix ${OBJDIR}/, ${SRCS:.c=.o})

#--- RULES ---#
${OBJDIR}/%.o : %.c
	@${CC} ${CFLAGS} -I${INCDIR} -I. -c $< -o $@
	
all				: 	 	pokeball libft $(NAME)
	
$(NAME)			: 		$(OBJDIR) $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(CNAME) sucessefully compiled 📁.${RESET}"

$(OBJDIR)		:
	@$(MK) ${OBJDIR}

libft			:
	@$(MAKE) -C $(LDIR)

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

clean			:
	@$(RM) $(OBJS)
	@$(RM)r $(OBJDIR)
	@$(MAKE) -C $(LDIR) clean
	
fclean			: 		clean	
	@$(RM) $(NAME)
	@$(MAKE) -C $(LDIR) fclean
	@echo "$(CNAME) object files and executable successfully removed 🗑.${RESET}"

re				: 		fclean all

.PHONY			: 		all clean fclean re