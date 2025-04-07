using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PoloClubApp
{
    internal class Device
    {
       
        public string name { get; private set; }
        public int Id { get; private set; }
        public string playerName { get; private set; }
        


        public Device(int id, string name)
        {
            this.Id = id;
            this.name = name;
            
        }

        public bool IsAssigned(int deviceId, Club myClub)
        {

            Device device = myClub.GetDeviceById(deviceId);
            return device.playerName != null;
        }

        
        public bool AsignDevice(string playerName, int id, Club myClub)
        {
            if(this.IsAssigned(id, myClub))
                return false;
            if (this is IWearable)
            { 
                if (((IWearable)this).GetWaterResistanceMeters() < 3)
                    {
                        return false;
                    }
                }
            this.playerName = playerName;
            return true;
        }

        public bool UnassignDevice(int id, Club myClub)
        {
         
            Device deviceToReturn = myClub.GetDeviceById(id);
            if(IsAssigned(id, myClub))
            {
                deviceToReturn.playerName = null;
                return true;
            }else
            {
                return false;
            }
        }

        public virtual string GetDetails()
        {
            return $"Device ID: {Id}, Device Name: {name}, Player Name: {playerName}";
        }
    }
}
