#!/usr/bin/python


import random, sys
from optparse import OptionParser

class getlines:
    def __init__(self, filename):
        f = open(filename, 'r')
        self.lines = f.readlines()
        f.close()

    def getlist(self):
        return self.lines

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [OPTION]... FILE1 FILE2

select or reject lines common to two files."""

    parser = OptionParser(version=version_msg,
                          usage=usage_msg)
    parser.add_option("-1",
                      action="store_true", dest="column1", default=False,
                      help="do not output first column")

    parser.add_option("-2",
                      action="store_true", dest="column2", default=False,
                      help="do not output second column")
    
    parser.add_option("-3",
                      action="store_true", dest="column3", default=False,
                      help="do not output third column")

    parser.add_option("-u",
                      action="store_true", dest="uoption", default=False,
                      help="input is unsorted")
    
    options, args = parser.parse_args(sys.argv[1:])

    column1 = bool(options.column1)
    column2 = bool(options.column2)
    column3 = bool(options.column3)
    uoption = bool(options.uoption)    
    
    if len(args) != 2:
        parser.error("wrong number of operands")
    
    input_file1 = args[0]
    input_file2 = args[1]

    try:
        # get list of lines
        firstfile = getlines(input_file1)
        secondfile = getlines(input_file2)
        firstlist = firstfile.getlist()
        secondlist = secondfile.getlist()

        # remove the \n from each list entry 
        editlist1 = []
        for i in firstlist:
            editlist1.append(i.rstrip('\n'))

        editlist2 = []
        for i in secondlist:
            editlist2.append(i.rstrip('\n'))

        # printlist will store the final printout
        # count counts which element of second file currently iterating
        printlist = []
        count = 0

        # if -u option was not specified
        if uoption == False:          
            for i in range(len(editlist1)):
                # if no more elements left in second file, append the rest of file1
                if count == len(editlist2):
                    if not column1:
                        printlist.append(editlist1[i])

                #iterate through file 2
                for j in range(len(editlist2)):  
                    if j < count:
                        continue

                    #if found match, append the common line
                    if editlist1[i] == editlist2[j]:
                        if not column3:
                            if not column2:
                                if not column1:
                                    printlist.append("                "+editlist1[i])
                                else:
                                    printlist.append("        "+editlist1[i])
                            else:
                                if not column1:
                                    printlist.append("        "+editlist1[i])
                                else:
                                    printlist.append(editlist1[i])
                        count += 1
                        break
                        
                    #if greater, append line from second file
                    if editlist1[i] > editlist2[j]:
                        if not column2:
                            if not column1:
                                printlist.append("        "+editlist2[j])
                            else:
                                printlist.append(editlist2[j])
                        count += 1
                        continue
                    
                    #if less, append line from first file
                    if editlist1[i] < editlist2[j]:
                        if not column1:
                            printlist.append(editlist1[i])
                        break

            #append the rest of lines from second file        
            if count < len(editlist2):
                for i in range(len(editlist2)):
                    if i < count:
                        continue
                    if not column2:
                        if not column1:
                            printlist.append("        "+editlist2[i])
                        else:
                            printlist.append(editlist2[i])

        #if -u option was specified                    
        else:
            x = len(editlist2)

            #create dictionary to hold all lines
            dict = {}
            for index in range(len(editlist2)):
                dict[index] = editlist2[index]
            for index in range(len(editlist1)):
                dict[index+x] = editlist1[index]

            #compare each value in first file with all of second file, append to third column if found match
            for i in range(len(editlist1)):
                for j in range(len(editlist2)):
                    if editlist1[i] == editlist2[j]:
                        if dict[j] != "":
                            if not column3:
                                if not column2:
                                    if not column1:
                                        printlist.append("                "+editlist1[i])
                                    else:
                                        printlist.append("        "+editlist1[i])
                                else:
                                    if not column1:
                                        printlist.append("        "+editlist1[i])
                                    else:
                                        printlist.append(editlist1[i])
                            dict[i+x]=""
                            dict[j]=""
                            break
                #append lines from first file that had no match
                if dict[i+x] != "":
                    if not column1:
                        printlist.append(editlist1[i])

            #append the rest of the lines form second file
            for index in range(len(editlist2)):
                if dict[index] != "":
                    if not column2:
                        if not column1:
                            printlist.append("        "+editlist2[index])
                        else:
                            printlist.append(editlist2[index])

        #print out everything            
        for index in printlist:
            sys.stdout.write(index)
            sys.stdout.write('\n')
        
    except IOError as errno_strerror:
        parser.error("I/O error({0}): {1}".
                     format(errno, strerror))

if __name__ == "__main__":
    main()
