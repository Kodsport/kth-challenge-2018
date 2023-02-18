#!/usr/bin/env python3
from sys import stdin
import sys
import re
import io

pat_integer = "(0|-?[1-9]\d*)"
pat_name = "([A-Za-z]{1,10})"
pat_enemy = pat_name+" "+pat_name+"\n"
pat_group = re.compile("\s*([A-Za-z]{1,10})(\s+[A-Za-z]{1,10})*\s*\n")

EXIT_AC = 42
EXIT_WA = 43

judge_out = ""
judge_err = ""
auth_out = ""
judgefile = "judgemessage.txt"
judgeerror = "judgeerror.txt"
authormessage = "authormessage.txt"

def judge_error(msg):
  judge_err.write(msg+'\n')
  judge_err.flush()
  raise Exception(msg)

def input_error(msg):
  judge_out.write(msg+'\n')
  judge_out.flush()
  sys.exit(EXIT_WA)

def author_msg(msg):
  auth_out.write(msg+'\n')
  auth_out.flush()

def accept():
  sys.exit(EXIT_AC)

def main():
  args = sys.argv
  judge_in = open(args[1], "r")
  judge_ans = open(args[2], "r")
  global judgefile, judgeerror, authormessage, judge_err, judge_out, auth_out
  judgefile = args[3]+"/"+judgefile
  judgeerror = args[3]+"/"+judgeerror
  authormessage = args[3]+"/"+authormessage
  judge_err = open(judgeerror, "w")
  judge_out = open(judgefile, "w")
  auth_out = open(authormessage, "w")
  if(len(args) < 4):
    judge_error("USAGE: "+args[0]+" judgein judgeans feedbackdir < userout")
  user_out = stdin

  #read input data
  line = judge_in.readline()
  [children,enemies,maxgroup] = [int(x) for x in line.split()]
  names = []
  dislikes = {}
  for x in range(0, children):
    line = judge_in.readline()
    name = line.strip()
    names.append(name)
    dislikes[name] = []
  for x in range(0, enemies):
    line = judge_in.readline()
    [a,b] = [x.strip() for x in line.split()]
    dislikes[a].append(b)
    dislikes[b].append(a)      
  
  #read answer data
  line = judge_ans.readline() 
  if(not re.match(pat_integer+"\n", line)):
    judge_error("Problem answer is invalid - no answer")
  best = int(line)

  #read output data
  try:
    line = user_out.readline()
  except:
    input_error("not valid string")

  if(not re.match(pat_integer+"\n", line)):
    author_msg("Misformated input: group count")
    input_error("Misformated input")
  groups = int(line)
  if(best != groups):
    author_msg("Wrong number of groups")
    input_error("{0} != {1} ".format(groups, best))
  persons = []
  for x in range(0, groups):
    try:
      line = user_out.readline()
    except:
      input_error("not valid string")
    if(not pat_group.match(line)):
      author_msg("Misformated input: group members")
      input_error("Misformated input line: >"+line+"<")
    group = line.split()
    if(len(group) > maxgroup):
        author_msg("You have too many children in a group")
        input_error("Too many children: %d > %d"%(len(group),c))
    for p in group:
      if(p not in dislikes):
        author_msg("You have a person who doesn't exist!")
        input_error("Nonexistant person: "+p)
      if(persons.count(p) != 0):
        author_msg("You have the same person in two groups!")
        input_msg("Person "+p+" already appeared")
      persons.append(p)
      for q in group:
        if(dislikes[p].count(q) != 0):
          author_msg("Two enemies are in the same group")
          input_error(p+" doesn't like "+q+" group")
  if(len(persons) != children):
        author_msg("Not everyone is in a group!")
        input_error("{0} people expected {1}".format(len(persons), children))
  try:
    line = user_out.readline()
  except:
    input_error("not valid string")
  if(len(line) != 0):
    author_msg("Trailing trash after outdata")
    input_error("Trash after answer")
  accept()

main()

