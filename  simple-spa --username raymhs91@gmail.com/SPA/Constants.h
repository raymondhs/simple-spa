/*
 * @author: Raymond
 */
#pragma once

#include <set>

typedef enum NodeType {
	TNODE = 0, PROGRAM /*1*/, PROCEDURE /*2*/,
	STMTLST /*3*/, STMT /*4*/, ASSIGN /*5*/,
	WHILE /*6*/, IF /*7*/, CONST /*8*/, EXPR /*9*/,
	PLUS /*10*/, MINUS /*11*/, TIMES /*12*/, VAR /*13*/, PROGLINE /*14*/, CALL /*15*/
};

typedef enum QNodeType {
	QSTMT		= 1<<1,
	QSYN 		= 1<<2,
	QPROGLINE	= 1<<3,
	QASSIGN		= 1<<4,
	QWHILE		= 1<<5,
	QCONST		= 1<<6,
	QPROC		= 1<<7,
	QVAR		= 1<<8,
	QCALL		= 1<<9,
	QIF         = 1<<10,
	QSELECT, QSUCHTHAT, QWITH, QPATTERNLIST,
	QMODIFIES, QUSES, QPARENT, QPARENTT, QFOLLOWS, QFOLLOWST,
	QPATTERN, QSTRING, QANY,
	QPLUS, QMINUS, QTIMES, QINT, QBOOL, QCALLT, QNEXT, QNEXTT,
	QAFFECT, QAFFECTT, QSTMTLST
};

typedef int STMT_NO;
typedef int VAR_IDX;
typedef int PROC_IDX;

typedef std::string PROC_NAME;
typedef std::set<STMT_NO> STMT_SET;
typedef std::set<VAR_IDX> VAR_SET;
typedef std::set<PROC_IDX> PROC_SET;

#define INF 2147483647