/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file apps/postfix_eval.h
 *
 * \brief Header file for the postfix expression evaluator application.
 *
 * This application evaluates postifx mathematical expressions.
 * Supported operators:
 * - addition '+',
 * - subtraction '-',
 * - multiplication '*',
 * - division '/',
 * - modulo '%',
 * - exponentiation '^'
 * .
 * Every operator takes exactly two arguments.
 *
 * \author Your Name
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 *  This file is part of UPOalglib.
 *
 *  UPOalglib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  UPOalglib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef POSTFIX_EVAL_H
#define POSTFIX_EVAL_H


#include <stdio.h>


/**
 * \brief Evaluates the given postfix expression.
 *
 * \param expr The input postfix expression to evaluate.
 * \param res Output parameters holding the result if the expression.
 * \return `1` if the input expression is well-formed, or `0` otherwise.
 */
static int eval_postfix(const char *expr, long *res);

/**
 * \brief Evaluates each line of the given file as a postfix math expression.
 *
 * \param fp The input file
 */
static void eval_lines(FILE *fp);

/**
 * \brief Prints a 'usage' message on the standard error.
 *
 * \param progname The name of the executable program.
 */
static void usage(const char *progname);


#endif /* POSTFIX_EVAL_H */
