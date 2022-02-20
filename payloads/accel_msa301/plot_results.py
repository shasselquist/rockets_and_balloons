import numpy as np
from matplotlib import pyplot as plt
from astropy.table import Table

#Put the following at the top of each text file:
# ax,ay,az

file='ANALOG08.TXT'

data=Table.read(file,format='csv')
#We believe there are only 14 bits, so +/- 16 g means that 2**13 is 16g and -2**13 is -16g.
#So that means the bit range should be. -8192 to 8192. so that's 8192/16 = 512 per g.

#We sample 10 times per second, so let's make time array. Note that the thing doesn't actually track time:
time_arr=np.arange(0,len(data['ax'])/10,0.1)

fig1, ax = plt.subplots(2,2,figsize=(8,8),dpi=300)

ax[0,0].plot(time_arr,data['ax']/512)
ax[0,1].plot(time_arr,data['ay']/512)
ax[1,0].plot(time_arr,data['az']/512)
ax[1,1].plot(time_arr,np.sqrt(data['ax']**2+data['ay']**2+data['az']**2)/512)

ax[0,0].set_xlabel('Time (s)')
ax[0,1].set_xlabel('Time (s)')
ax[1,0].set_xlabel('Time (s)')
ax[1,1].set_xlabel('Time (s)')

ax[0,0].set_ylabel('ax (g)')
ax[0,1].set_ylabel('ay (g)')
ax[1,0].set_ylabel('az (g)')
ax[1,1].set_ylabel('|a| (g)')

#After things sit on the launchpad for a bit, we may want
#to really zoom in on the time:
for i in range(2):
    for j in range(2):
        ax[i,j].set_xlim(20,60)
        ax[i,j].grid()
        print('a')




plt.savefig(file+'_.jpg',dpi=300)
plt.clf()
