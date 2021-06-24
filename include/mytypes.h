/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytypes.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takuya <takuya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:55:07 by takuya            #+#    #+#             */
/*   Updated: 2021/06/24 15:57:44 by takuya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYTYPES_H
# define MYTYPES_H

# define STR 0      // 文字列
# define RDIR 1     // >
# define RRDIR 2    // >>
# define LDIR 3     // <
# define LLDIR 4    // <<
# define REDFD 5   // redirect file descriptor n>, n<, n>>
# define MYSPACE 6    //  
# define SQUOTE 7   // '
# define DQUOTE 8   // "
# define PIPE 9     // |
// # define DPIPE 10   // ||
# define AND 11     // &
// # define DAND 12    // &&
# define SCOLON 13  // ;
// # define DSCOLON 14 // ;;
// # define DOLL 15    // $ 使わなかった
// # define ESC 16     // '\'
// # define SSTR 17    // single_quote内の文字列。 使わなかった。
# define RINT 18    // 2>file の[2]


#endif