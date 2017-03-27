#!/usr/bin/env python
# -*- coding: utf-8 -*-
## @copyright
#   Software License Agreement (BSD License)
#
#   Copyright (c) 2017, Jorge De La Cruz, Carmen Castano.
#   All rights reserved.
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#
#       1. Redistributions of source code must retain the above copyright notice, this
#          list of conditions and the following disclaimer.
#       2. Redistributions in binary form must reproduce the above copyright notice,
#          this list of conditions and the following disclaimer in the documentation
#         and/or other materials provided with the distribution.
#
#    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#    POSSIBILITY OF SUCH DAMAGE.


__author__ = 'Jorge De La Cruz, Carmen Castano'
__copyright__ = 'Copyright (c) 2017 Jorge De La Cruz, Carmen Castano'

__license__ = 'BSD'
__maintainer__ = 'Jorge De La Cruz'
__email__ = 'delacruz@igm.rwth-aachen.de'

import sys

## Path to FreeCAD library
# change this by your FreeCAD library path
sys.path.append('/usr/lib/freecad/lib')
import FreeCAD as App
import Import
from datetime import datetime

class GetParameters:
    def __init__(self):
        self.filePath = '/home/jdelacruz/Downloads/KonzeptB_lang090715.stp'

    def loadCAD(self):
        print('Starting to load the CAD file, please be patient!...')
        Import.open(self.filePath)
        self.handler = App.ActiveDocument
        self.parts = self.handler.Objects
        print('CAD model loaded!')

    def writeTxt(self):
        f = open('data.txt','a')
        print >>f, 'Name \t Label'
        self.i = 0
        self.size = len(self.parts)
        self.names = range(self.size)
        self.labels = range(self.size)
        for self.part in self.parts:
            self.names[self.i] = self.part.Name
            self.labels[self.i] = self.part.Label
            print >>f, self.part.Name+"\t"+self.part.Label
            self.i += 1
        f.close()

        print('The txt file has been created successfully!')

if __name__ == '__main__':
        data = GetParameters()
        data.loadCAD()
        data.writeTxt()
