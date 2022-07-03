ENGLISH VERSION
This is the basic introduction to RASM

(Please read the LICENSE agreement before doing anything, the law will be prosecuted!)

In this project, I will try to write a cross-platform virtual machine based on Windows system and make my own Assembly language with Turing-complete

This project is divided into two major frameworks: virtual machine level and assembler level. The source code of virtual machine level is in the source/RVM folder, and the source code of assembler level is in the source/ASM folder

The executable files are in the bin folder 
 
Because of the complexity of the MAKEFILE protocols and operations, I also wrote a lightweight MAKEFILE with the source file in source/RMAKE

I will synchronize the source code to Github at the first time, CSDN at the second time, and xueersi community at the third time, so for the latest updates, please follow Github



Update-log is a protocol file. Work-diary is a joke full of nonsense and recent status



This project is written by C language, whether virtual machine, or assembler, at least the running platform is required to have stdio.h, stdlib. h, string. h and other standard libraries and interfaces.



If you have any suggestions or bugs for the project, please send an email to woshiquxiangrong@outlook.com and ask the email to be sent in the following format, otherwise it will not be processed:

Title: RASM_ Overview of problems

The first line of the content is your email address, the type of question, and I will reply to the corresponding email address

The following content describes the problem in detail. The submitted code should be commented and all identifiers should be prefixed with RASM_. Violations will be returned for rectification and will not be accepted

Malicious mail will be blacklisted!


temporary

* Introductory documentation will be written after the project is successful -2022/6/11



中文版本（我是中国人，我爱中国！！）
这是RASM的基本介绍文档

(请先阅读LICENSE协议再做任何事，违法必究！)

在这个项目中，我将尝试基于windows系统编写跨平台的虚拟机并由此自制具有图灵完备性的汇编语言

本项目分为两大框架：虚拟机层面和汇编器层面，虚拟机层面的源码见source/RVM文件夹，汇编器层面的源码见source/ASM文件夹

可执行文件在bin文件夹里

因为MAKEFILE的协议和操作复杂的原因，我还写了一个轻量级的MAKEFILE，源文件在source/RMAKE里

我会将源码第一时间同步更新到github上，第二时间同步更新到csdn上，第三时间同步更新到学而思社区上，所以想要获得最新的动态，请关注github

LICENSE是协议文件、UPDATE-LOG是更新日志文件、WORK-DIARY.nonsense是充满废话的吐槽和最近的一些状态，backup放着没用的备份代码，你完全可以把他删去

本项目由c语言编写，无论是虚拟机，还是汇编器，至少要求运行平台有stdio.h、stdlib.h、string.h等标准库

如果你对本项目有什么建议或者发现一些漏洞的话，欢迎发邮件到woshiquxiangrong@outlook.com，并要求邮件按以下格式发送，否则不予处理：
标题：RASM_问题概述
内容的第一行写上你的邮箱，问题类型，我将会回信到相应的邮箱
接下来的内容就对问题进行具体的描述，提交的代码要写好注释，并把里面所有的标识符按RASM_为前缀，违反规则将退回整改并不予接收

恶意邮件将被列入黑名单!

临时
	* 介绍文档将在项目成功后编写 -2022/6/11