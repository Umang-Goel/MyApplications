import wx
import wave, struct
import pyaudio
import sys
import os
from os.path import *
from sys import byteorder
from array import array
from struct import pack
from datetime import datetime


ar = []
mod = []
mix = []
params = []
amp1 = "1.0"
chunk = 1024
THRESHOLD = 1500
CHUNK_SIZE = 1024
FORMAT = pyaudio.paInt16
RATE = 44100

class Example(wx.Frame):

    def __init__(self, *args, **kw):
        super(Example, self).__init__(*args, **kw)
        self.InitUI()
	self.mix1 = 0
	self.mod1 = 0
	self.rev1 = 0
	self.mix2 = 0
	self.mod2 = 0
	self.rev2 = 0
	self.mix3 = 0
	self.mod3 = 0
	self.rev3 = 0
	self.amp_fact1 = 1
	self.shift_fact1 = 0
	self.scale_fact1 = 1
	self.amp_fact2 = 1
	self.shift_fact2 = 0
	self.scale_fact2 = 1
	self.amp_fact3 = 1
	self.shift_fact3 = 0
	self.scale_fact3 = 1
	self.fname1 = "none"
	self.fname2 = "none"
	self.fname3 = "none"

    def InitUI(self):   

        pnl = wx.Panel(self)

	wx.StaticBox(pnl, label='Wave1', pos=(5, 5), size=(240, 450))
	
	self.filename1 = wx.StaticText(pnl, label='No file Selected', pos=(120, 40))
        cbtn = wx.Button(pnl, label='Choose', pos=(20, 30))
        cbtn.Bind(wx.EVT_BUTTON, self.Select_file1)
	
	wx.StaticText(pnl, label='Amplitude', pos=(20, 80))	
	self.amp1 = wx.StaticText(pnl, label='1.0', pos=(190, 80))
	amp1= wx.Slider(pnl, value=10, minValue=1, maxValue=50, pos=(30, 80+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        amp1.Bind(wx.EVT_SCROLL, self.OnAmplitude1)

	wx.StaticText(pnl, label='Time Shift', pos=(20, 100+40))	
	self.shift1 = wx.StaticText(pnl, label='0.0', pos=(190, 140))
	shft1 = wx.Slider(pnl, value=0, minValue=-1000, maxValue=1000, pos=(30, 140+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        shft1.Bind(wx.EVT_SCROLL, self.OnTimeShift1)

	wx.StaticText(pnl, label='Time Scaling', pos=(20, 160+40))	
	self.scale_val1 = wx.StaticText(pnl, label='1.0', pos=(190, 200))
	scale1 = wx.Slider(pnl, value=1, minValue=-8, maxValue=8, pos=(30, 200+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        scale1.Bind(wx.EVT_SCROLL, self.OnTimeScale1)

	rev1 = wx.CheckBox(pnl, label='Time Reversal', pos=(20, 220+40))
        rev1.SetValue(False)
        rev1.Bind(wx.EVT_CHECKBOX, self.is_reverse1)

	mod1 = wx.CheckBox(pnl, label='Select for Modulation', pos=(20, 260+30))
        mod1.SetValue(False)
        mod1.Bind(wx.EVT_CHECKBOX, self.is_modulated1)

	mix1 = wx.CheckBox(pnl, label='Select for Mixing', pos=(20, 290+30))
        mix1.SetValue(False)
        mix1.Bind(wx.EVT_CHECKBOX, self.is_mixed1)
        
	cbtn = wx.Button(pnl, label='Play', pos=(20, 320+40))
        cbtn.Bind(wx.EVT_BUTTON, self.play1)

	#Box2
	wx.StaticBox(pnl, label='Wave2', pos=(5+240+10, 5), size=(240, 450))
	self.filename2 = wx.StaticText(pnl, label='No file Selected', pos=(120+250, 40))
        cbtn = wx.Button(pnl, label='Choose', pos=(20+240+10, 30))
        cbtn.Bind(wx.EVT_BUTTON, self.Select_file2)


	wx.StaticText(pnl, label='Amplitude', pos=(20+240+10, 80))	
	self.amp2 = wx.StaticText(pnl, label='1.0', pos=(190+250, 80))
	amp2 = wx.Slider(pnl, value=10, minValue=1, maxValue=50, pos=(280, 80+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        amp2.Bind(wx.EVT_SCROLL, self.OnAmplitude2)

	wx.StaticText(pnl, label='Time Shift', pos=(270, 100+40))	
	self.shift2 = wx.StaticText(pnl, label='0.0', pos=(190+250, 140))
	shft2 = wx.Slider(pnl, value=0, minValue=-1000, maxValue=1000, pos=(280, 140+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        shft2.Bind(wx.EVT_SCROLL, self.OnTimeShift2)

	wx.StaticText(pnl, label='Time Scaling', pos=(270, 160+40))	
	self.scale_val2 = wx.StaticText(pnl, label='1.0', pos=(190+250, 200))
	scale2 = wx.Slider(pnl, value=1, minValue=-8, maxValue=8, pos=(280, 200+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        scale2.Bind(wx.EVT_SCROLL, self.OnTimeScale2)

	rev1 = wx.CheckBox(pnl, label='Time Reversal', pos=(20+240+10, 220+40))
        rev1.SetValue(False)
        rev1.Bind(wx.EVT_CHECKBOX, self.is_reverse2)

	mod1 = wx.CheckBox(pnl, label='Select for Modulation', pos=(20+240+10, 260+30))
        mod1.SetValue(False)
        mod1.Bind(wx.EVT_CHECKBOX, self.is_modulated2)

	mix1 = wx.CheckBox(pnl, label='Select for Mixing', pos=(20+240+10, 290+30))
        mix1.SetValue(False)
        mix1.Bind(wx.EVT_CHECKBOX, self.is_mixed2)

	play_btn2 = wx.Button(pnl, label='Play', pos=(20+250, 320+40))
        play_btn2.Bind(wx.EVT_BUTTON, self.play2)

	#Box3
	wx.StaticBox(pnl, label='Wave3', pos=(5+240+10+240+10, 5), size=(240, 450))
	self.filename3 = wx.StaticText(pnl, label='No file Selected', pos=(120+500, 40))
        cbtn = wx.Button(pnl, label='Choose', pos=(20+240+10+240+10, 30))
        cbtn.Bind(wx.EVT_BUTTON, self.Select_file3)

	wx.StaticText(pnl, label='Amplitude', pos=(520, 80))	
	self.amp3 = wx.StaticText(pnl, label='1.0', pos=(190+500, 80))
	sld = wx.Slider(pnl, value=10, minValue=1, maxValue=50, pos=(530, 80+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        sld.Bind(wx.EVT_SCROLL, self.OnAmplitude3)

	wx.StaticText(pnl, label='Time Shift', pos=(520, 100+40))	
	self.shift3 = wx.StaticText(pnl, label='0.0', pos=(190+500, 140))
	sld = wx.Slider(pnl, value=0, minValue=-1000, maxValue=1000, pos=(530, 140+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        sld.Bind(wx.EVT_SCROLL, self.OnTimeShift3)

	wx.StaticText(pnl, label='Time Scaling', pos=(520, 160+40))	
	self.scale_val3 = wx.StaticText(pnl, label='1.0', pos=(190+500, 200))
	sld = wx.Slider(pnl, value=1, minValue=-8, maxValue=8, pos=(530, 200+20), size=(150, -1), style=wx.SL_HORIZONTAL)        
        sld.Bind(wx.EVT_SCROLL, self.OnTimeScale3)

	rev1 = wx.CheckBox(pnl, label='Time Reversal', pos=(20+240+10+240+10, 230+40))
        rev1.SetValue(False)
        rev1.Bind(wx.EVT_CHECKBOX, self.is_reverse3)

	mod1 = wx.CheckBox(pnl, label='Select for Modulation', pos=(20+240+10+240+10, 260+30))
        mod1.SetValue(False)
        mod1.Bind(wx.EVT_CHECKBOX, self.is_modulated3)

	mix1 = wx.CheckBox(pnl, label='Select for Mixing', pos=(20+240+10+240+10, 290+30))
        mix1.SetValue(False)
        mix1.Bind(wx.EVT_CHECKBOX, self.is_mixed3)

	play_btn3 = wx.Button(pnl, label='Play', pos=(20+500, 320+40))
        play_btn3.Bind(wx.EVT_BUTTON, self.play3)

	wx.StaticText(pnl, label='Modulation:', pos=(50, 470))	
	play_btn4 = wx.Button(pnl, label='Play', pos=(50,490))
        play_btn4.Bind(wx.EVT_BUTTON, self.modulation)
	
	wx.StaticText(pnl, label='Mixing:', pos=(320, 470))	
	play_btn4 = wx.Button(pnl, label='Play', pos=(320, 490))
        play_btn4.Bind(wx.EVT_BUTTON, self.mixing)
	
	wx.StaticText(pnl, label='Recording:', pos=(620, 470))	
	play_btn4 = wx.Button(pnl, label='Record', pos=(620, 490))
        play_btn4.Bind(wx.EVT_BUTTON, self.record_to_file)
	
        self.SetSize((750, 600))
        self.SetTitle('Wave Mixer')
        self.Centre()
        self.Show(True)   

    def OnClose(self, e):
        
        self.Close(True)            

    def is_reverse1(self, e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.rev1 = 1
	else:
	    self.rev1 = 0

    def is_reverse2(self, e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.rev2 = 1
	else:
	    self.rev2 = 0

    def is_reverse3(self, e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.rev3 = 1
	else:
	    self.rev3 = 0

    def is_modulated1(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mod1 = 1
	else:
	    self.mod1 = 0

    def is_modulated2(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mod2 = 1
	else:
	    self.mod2 = 0

    def is_modulated3(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mod3 = 1
	else:
	    self.mod3 = 0

    def is_mixed1(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mix1 = 1
	else:
	    self.mix1 = 0

    def is_mixed2(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mix2 = 1
	else:
	    self.mix2 = 0

    def is_mixed3(self,e):
	sender = e.GetEventObject()
        isChecked = sender.GetValue()		        
        if isChecked:
            self.mix3 = 1
	else:
	    self.mix3 = 0

    def OnAmplitude1(self,e):
	obj = e.GetEventObject()
        self.amp_fact1 = (obj.GetValue()*1.0)/10
	self.amp1.SetLabel(str(self.amp_fact1))

    def OnAmplitude2(self,e):
	obj = e.GetEventObject()
        self.amp_fact2 = (obj.GetValue()*1.0)/10
	self.amp2.SetLabel(str(self.amp_fact2))

    def OnAmplitude3(self,e):
	obj = e.GetEventObject()
        self.amp_fact3 = (obj.GetValue()*1.0)/10
	self.amp3.SetLabel(str(self.amp_fact3))

    def OnTimeShift1(self,e):
	obj = e.GetEventObject()
        self.shift_fact1 = (obj.GetValue()*1.0)/1000
	self.shift1.SetLabel(str(self.shift_fact1))

    def OnTimeShift2(self,e):
	obj = e.GetEventObject()
        self.shift_fact2 = (obj.GetValue()*1.0)/1000
	self.shift2.SetLabel(str(self.shift_fact2))

    def OnTimeShift3(self,e):
	obj = e.GetEventObject()
        self.shift_fact3 = (obj.GetValue()*1.0)/1000
	self.shift3.SetLabel(str(self.shift_fact3))

    def OnTimeScale1(self,e):
	obj = e.GetEventObject()
	self.scale_fact1 = obj.GetValue()*1.0
	if(self.scale_fact1>=-1 and self.scale_fact1<=1):
		self.scale_fact1 = 1.0
	if(self.scale_fact1 < 0):
		self.scale_fact1 = -1.0 / self.scale_fact1
#        self.scale_fact1 = (obj.GetValue()*1.0)/10
	self.scale_val1.SetLabel(str(self.scale_fact1))

    def OnTimeScale2(self,e):
	obj = e.GetEventObject()
#        self.scale_fact2 = (obj.GetValue()*1.0)/10
	self.scale_fact2 = obj.GetValue()*1.0
	if(self.scale_fact2>=-1 and self.scale_fact2<=1):
		self.scale_fact2 = 1.0
	if(self.scale_fact2 < 0):
		self.scale_fact2 = -1.0 / self.scale_fact2
	self.scale_val2.SetLabel(str(self.scale_fact2))

    def OnTimeScale3(self,e):
	obj = e.GetEventObject()
#       self.scale_fact3 = (obj.GetValue()*1.0)/10
	self.scale_fact3 = obj.GetValue()*1.0
	if(self.scale_fact3>=-1 and self.scale_fact3<=1):
		self.scale_fact3 = 1.0
	if(self.scale_fact3 < 0):
		self.scale_fact3 = -1.0 / self.scale_fact3
	self.scale_val3.SetLabel(str(self.scale_fact3))

    def Select_file1(self,e):
	dlg = wx.FileDialog(self, message="Open a file", defaultDir=os.getcwd(),defaultFile="", style=wx.OPEN)
	if dlg.ShowModal() == wx.ID_OK:
		self.fname1 = str(dlg.GetPath())
		self.filename1.SetLabel(basename(str(dlg.GetPath())))
	dlg.Destroy()

    def Select_file2(self,e):
	dlg = wx.FileDialog(self, message="Open a file", defaultDir=os.getcwd(),defaultFile="", style=wx.OPEN)
	if dlg.ShowModal() == wx.ID_OK:
		self.fname2 = str(dlg.GetPath())
		self.filename2.SetLabel(basename(str(dlg.GetPath())))
	dlg.Destroy()

    def Select_file3(self,e):
	dlg = wx.FileDialog(self, message="Open a file", defaultDir=os.getcwd(),defaultFile="", style=wx.OPEN)
	if dlg.ShowModal() == wx.ID_OK:
		self.fname3 = str(dlg.GetPath())
		self.filename3.SetLabel(basename(str(dlg.GetPath())))
	dlg.Destroy()

    def play1(self,e):
	if(self.fname1 == "none"):
		self.show_err_msg("No File Selected")
		return
	self.inp(0,self.fname1)
	self.amplify(ar[0],self.amp_fact1)
	self.time_shift(ar[0],self.shift_fact1,0)
	self.time_scale(ar[0],self.scale_fact1,0)
	if(self.rev1 == 1):
		ar[0].reverse()
	self.play(ar[0],"new"+basename(self.fname1),0)

    def play2(self,e):
	if(self.fname2 == "none"):
		self.show_err_msg("No File Selected")
		return
	self.inp(1,self.fname2)
	self.amplify(ar[1],self.amp_fact2)
	self.time_shift(ar[1],self.shift_fact2,1)
	self.time_scale(ar[1],self.scale_fact2,1)
	if(self.rev2 == 1):
		ar[1].reverse()
	self.play(ar[1],"new"+basename(self.fname2),1)

    def play3(self,e):
	if(self.fname3 == "none"):
		self.show_err_msg("No File Selected")
		return
	self.inp(2,self.fname3)
	self.amplify(ar[2],self.amp_fact3)
	self.time_shift(ar[2],self.shift_fact3,2)
	self.time_scale(ar[2],self.scale_fact3,2)
	if(self.rev3 == 1):
		ar[2].reverse()
	self.play(ar[2],"new"+basename(self.fname3),2)

    def play(self,res,fname,pos):
	integer_data = tuple(res)
	total_samples = params[pos][3]
	fmt = "%ih" % total_samples 
	raw_data = struct.pack(fmt, *integer_data)
	var = wave.open(fname,"wb")
#	params[pos][3] /= 2
	var.setparams(tuple(params[pos]))
	var.writeframes(raw_data)
	var.close()
	wf = wave.open(fname, 'rb')
	p = pyaudio.PyAudio()
		# open stream based on the wave object which has been input.
	stream = p.open(format =
			p.get_format_from_width(wf.getsampwidth()),
			channels = wf.getnchannels(),
			rate = wf.getframerate(),
			output = True)

	# read data (based on the chunk size)
	data = wf.readframes(chunk)

	# play stream (looping from beginning of file to the end)
	while data != '':
	    # writing to the stream is what *actually* plays the sound.
	    stream.write(data)
	    data = wf.readframes(chunk)
		# cleanup stuff.
	stream.close()    
	p.terminate()	

    def amplify(self,inp,fact):
	for x in range (len(inp)):
		inp[x] = inp[x]*fact
		if(inp[x] >= 2**15 ):
			inp[x] = 2**15 -1
		if(inp[x] < -2**15):
			inp[x] = -2**15

    def time_shift(self,inp,fact,pos):
	tmp = []
	fact = fact*params[pos][2]*2
	fact = int(fact)
#	print "Fact is ",
#	print fact
	if(fact < 0):
		for x in range(-fact):
			tmp.append(0)
		for x in range(len(inp)):
			tmp.append(inp[x])
	else :
		for x in range(fact,len(inp)):
			tmp.append(inp[x])
	params[pos][3] = len(tmp)
	ar[pos] = tmp
	
    def time_scale(self,inp,fact,pos):
#       left = []
#	right = []
	res = []
	x = 0
	while(int(fact*x)<len(inp)):
		res.append(inp[int(x*fact)])
		x+=1
	ar[pos] = res
	params[pos][3] = len(res)

#	print "in time scale length inp",
#	print len(inp)
#	for x in range(0,len(inp),2):
#		left.append(inp[x])
#		if(x+1 < len(inp)):
#			right.append(inp[x+1])
#	x=0
#	while(int(fact*x)<len(left)):
#		res.append(left[int(x*fact)])
#		res.append(right[int(x*fact)])
#		x+=1


    def modulation(self,e):
	tmp = []
	max_len = -1
	frame_rate = -1
	if(self.mod1 == 1):
		if(self.fname1 == "none"):
			self.show_err_msg("File 1 not Selected")
			return
		self.inp(0,self.fname1)
		self.amplify(ar[0],self.amp_fact1)
		self.time_shift(ar[0],self.shift_fact1,0)
		self.time_scale(ar[0],self.scale_fact1,0)
		if(self.rev1 == 1):
			ar[0].reverse()
		if(max_len<len(ar[0])):
			max_len = len(ar[0])
		params[3] = []
		for x in range(len(params[0])):
			params[3].append(params[0][x])
		if(frame_rate == -1):
			frame_rate = params[0][2]
		elif(frame_rate != params[0][2]):
			return
	if(self.mod2 == 1):
		if(self.fname2 == "none"):
			self.show_err_msg("File 2 not Selected")
			return
		self.inp(1,self.fname2)
		self.amplify(ar[1],self.amp_fact2)
		self.time_shift(ar[1],self.shift_fact2,1)
		self.time_scale(ar[1],self.scale_fact2,1)
		if(self.rev2 == 1):
			ar[1].reverse()
		if(max_len<len(ar[1])):
			max_len = len(ar[1])
		params[3] = []
		for x in range(len(params[1])):
			params[3].append(params[1][x])
		if(frame_rate == -1):
			frame_rate = params[1][2]
		elif(frame_rate != params[1][2]):
			return
	if(self.mod3 == 1):
		if(self.fname3 == "none"):
			self.show_err_msg("File 3 not Selected")
			return
		self.inp(2,self.fname3)
		self.amplify(ar[2],self.amp_fact3)
		self.time_shift(ar[2],self.shift_fact3,2)
		self.time_scale(ar[2],self.scale_fact3,2)
		if(self.rev3 == 1):
			ar[2].reverse()
		if(max_len<len(ar[2])):
			max_len = len(ar[2])
		params[3] = []
		for x in range(len(params[2])):
			params[3].append(params[2][x])
		if(frame_rate == -1):
			frame_rate = params[2][2]
		elif(frame_rate != params[2][2]):
			return
	if(max_len == -1):
		self.show_err_msg("No wave seleected for modulation")
		return
	res = []
	while(x<max_len):
		tmp = 1
		if(self.mod1 == 1 and x< len(ar[0])):
			tmp *= ar[0][x]
		if(self.mod2 == 1 and x< len(ar[1])):
			tmp *= ar[1][x]
		if(self.mod3 == 1 and x< len(ar[2])):
			tmp *= ar[2][x]
		if(tmp >= 2**15 ):
			tmp = 2**15 -1
		if(tmp < -2**15):
			tmp = -2**15
		res.append(tmp)
		x+=1
	params[3][3] = len(res)
	self.play(res,"modulated.wav",3)

    def mixing(self,e):
	max_len = -1
	frame_rate  = -1
#	print "----------mix--------"
#	print self.mix1,self.mix2,self.mix3
	if(self.mix1 == 1):
		if(self.fname1 == "none"):
			self.show_err_msg("File 1 not Selected")
			return
		self.inp(0,self.fname1)
		self.amplify(ar[0],self.amp_fact1)
		self.time_shift(ar[0],self.shift_fact1,0)
		self.time_scale(ar[0],self.scale_fact1,0)
		if(self.rev1 == 1):
			ar[0].reverse()
		if(max_len<len(ar[0])):
			max_len = len(ar[0])    
		params[4] = []
		for x in range(len(params[0])):
			params[4].append(params[0][x])
		if(frame_rate == -1):
			frame_rate = params[0][2]
		elif(frame_rate != params[0][2]):
			return
	if(self.mix2 == 1):
		if(self.fname2 == "none"):
			self.show_err_msg("File 2 not Selected")
			return
		self.inp(1,self.fname2)
		self.amplify(ar[1],self.amp_fact2)
		self.time_shift(ar[1],self.shift_fact2,1)
		self.time_scale(ar[1],self.scale_fact2,1)
		if(self.rev2 == 1):
			ar[1].reverse()
		if(max_len<len(ar[1])):
			max_len = len(ar[1])
		params[4] = []
		for x in range(len(params[1])):
			params[4].append(params[1][x])
		if(frame_rate == -1):
			frame_rate = params[1][2]
		elif(frame_rate != params[1][2]):
			return
	if(self.mix3 == 1):
		if(self.fname3 == "none"):
			self.show_err_msg("File 3 not Selected")
			return
		self.inp(2,self.fname3)
		self.amplify(ar[2],self.amp_fact3)
		self.time_shift(ar[2],self.shift_fact3,2)
		self.time_scale(ar[2],self.scale_fact3,2)
		if(self.rev3 == 1):
			ar[2].reverse()
		if(max_len<len(ar[2])):
			max_len = len(ar[2])
		params[4] = []
		for x in range(len(params[2])):
			params[4].append(params[2][x])
		if(frame_rate == -1):
			frame_rate = params[2][2]
		elif(frame_rate != params[2][2]):
			return
	if(max_len == -1):
		self.show_err_msg("No wave seleected for mixing")
		return
	res = []
	for x in range(max_len):
		tmp = 0
		if(self.mix1 == 1 and x<len(ar[0])):
			tmp += ar[0][x]
		if(self.mix2 == 1 and x<len(ar[1])):
			tmp += ar[1][x]
		if(self.mix3 == 1 and x<len(ar[2])):
			tmp += ar[2][x]
		if(tmp >= 2**15 ):
			tmp = 2**15 -1
		if(tmp < -2**15):
			tmp = -2**15
		res.append(tmp)

#	print "len params[4]",
#	print len(params[4])
	params[4][3] = len(res)
	self.play(res,"mixed.wav",4)

    def show_err_msg(self,msg):
	    wx.MessageBox(msg, 'Error',wx.OK | wx.ICON_INFORMATION)

    def inp(self,pos,fname):
	stream = wave.open(fname,"rb")
	params[pos] = list(stream.getparams())

	raw_data = stream.readframes( params[pos][3] ) # Returns byte data
	stream.close()

#	total_samples = params[pos][3] * 2 
	total_samples = params[pos][3]

	fmt = "%ih" % total_samples # read signed 2 byte shorts

	integer_data = struct.unpack(fmt, raw_data)
	ar[pos] = list(integer_data)
	del raw_data 

    def is_silent(self,snd_data):
	    "Returns 'True' if below the 'silent' threshold"
	    return max(snd_data) < THRESHOLD

    def normalize(self,snd_data):
	    "Average the volume out"
	    MAXIMUM = 16384
	    times = float(MAXIMUM)/max(abs(i) for i in snd_data)

	    r = array('h')
	    for i in snd_data:
		r.append(int(i*times))
	    return r

    def trim(self,snd_data):
	    "Trim the blank spots at the start and end"
	    def _trim(snd_data):
		snd_started = False
		r = array('h')

		for i in snd_data:
		    if not snd_started and abs(i)>THRESHOLD:
			snd_started = True
			r.append(i)

		    elif snd_started:
			r.append(i)
		return r

	    # Trim to the left
	    snd_data = _trim(snd_data)

	    # Trim to the right
	    snd_data.reverse()
	    snd_data = _trim(snd_data)
	    snd_data.reverse()
	    return snd_data

    def add_silence(self,snd_data, seconds):
	    "Add silence to the start and end of 'snd_data' of length 'seconds' (float)"
	    r = array('h', [0 for i in xrange(int(seconds*RATE))])
	    r.extend(snd_data)
	    r.extend([0 for i in xrange(int(seconds*RATE))])
	    return r

    def record(self):
	    """
	    Record a word or words from the microphone and 
	    return the data as an array of signed shorts.

	    Normalizes the audio, trims silence from the 
	    start and end, and pads with 0.5 seconds of 
	    blank sound to make sure VLC et al can play 
	    it without getting chopped off.
	    """
	    p = pyaudio.PyAudio()
	    stream = p.open(format=FORMAT, channels=1, rate=RATE,
		input=True, output=True,
		frames_per_buffer=CHUNK_SIZE)

	    num_silent = 0
	    snd_started = False

	    r = array('h')

	    while 1:
		# little endian, signed short
		snd_data = array('h', stream.read(CHUNK_SIZE))
		if byteorder == 'big':
		    snd_data.byteswap()
		r.extend(snd_data)

		silent = self.is_silent(snd_data)


		if silent and snd_started:
		    num_silent += 1
		elif not silent and not snd_started:
		    snd_started = True

		if snd_started and num_silent > 30:
		    break

	    sample_width = p.get_sample_size(FORMAT)
	    stream.stop_stream()
	    stream.close()
	    p.terminate()

	    r = self.normalize(r)
	    r = self.trim(r)
	    r = self.add_silence(r, 0.5)
	    return sample_width, r

    def record_to_file(self,e):
	    "Records from the microphone and outputs the resulting data to 'path'"
	    sample_width, data = self.record()
	    data = pack('<' + ('h'*len(data)), *data)
	    lname = str(datetime.now())
	    lname = "record"+lname
	    wf = wave.open(lname, 'wb')
	    wf.setnchannels(1)
	    wf.setsampwidth(sample_width)
	    wf.setframerate(RATE)
	    wf.writeframes(data)
	    wf.close()

def main():
    for x in  range(3):
	    tmp = []
	    ar.append(tmp)
    for x in  range(5):
	    tmp = []
	    params.append(tmp)
    ex = wx.App()
    Example(None)
    ex.MainLoop()    


if __name__ == '__main__':
    main()   
