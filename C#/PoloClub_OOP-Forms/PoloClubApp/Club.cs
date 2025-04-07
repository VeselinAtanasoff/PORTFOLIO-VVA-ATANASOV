using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;

namespace PoloClubApp
{
    class Club
    {
        private string name;            
        private List<Device> devices;   

        public Club(string name)
        {
            this.name = name;
            this.devices = new List<Device>();
        }

        public string Name {get { return this.name; } } 


        //-----Provide your answers here-----

        public List<Device> GetWearables()
        {
            List<Device> wearables = new List<Device>();
            foreach (Device dev in this.devices)
            {
                if (dev is IWearable)
                {
                    wearables.Add(dev);
                }
            }
            return wearables;
        }

        public void AssignDevice(int id, string playerName, Club myClub)
        {
            Device deviceToAssign = GetDeviceById(id);
            deviceToAssign.AsignDevice(playerName, id, myClub);
        }

        public bool ReturnDevice(int id, Club myClub)
        {
            Device deviceToReturn = GetDeviceById(id);
            return deviceToReturn.UnassignDevice(id, myClub);

        }   

        public List<Device> GetAllAsignedDevicesPerPlayer(string playerName)
        {
            List<Device> devicesPerPlayer = new List<Device>();
            foreach (Device dev in this.devices)
            {
                if (dev.playerName == playerName)
                {
                    devicesPerPlayer.Add(dev);
                }
            }
            return devicesPerPlayer;
        }

        public string GenerateReportPerPlayer(string playerName)
        {
            List<Device> devicesPerPlayer = GetAllAsignedDevicesPerPlayer(playerName);
            string report = $"List of devices assigned to {playerName}:\n" +
                            $"===================================================\n";

            
            string phones = $"Phones\n" +
                            $"-----------\n";
            string wearables = $"Wearables\n" +
                               $"-----------\n";

            int phoneCount = 0;
            int wearableCount = 0;

            foreach (Device dev in devicesPerPlayer)
            {
                if (dev is SmartPhone)
                {
                    phones += $"Phone Id: {dev.Id}, name: {dev.name}\n";
                    phoneCount++;
                }
                else
                {
                    if (dev is SmartWatch)
                    {
                        wearables += $"SmartWatch Id: {dev.Id}, name: {dev.name}\n";
                    }
                    else if (dev is FitTracker)
                    {
                        wearables += $"FitTracker Id: {dev.Id}, name: {dev.name}\n";
                    }
                    wearableCount++;
                }
            }
            string overview = $"Total number of devices: {devicesPerPlayer.Count}\n" +
                              $"Number of phones: {phoneCount}\n" +
                              $"Number of wearables: {wearableCount}\n";
            
            report += phones + "\n" + wearables + "\n"+overview;

            return report;
        }   



        // -----The provided code below will not be graded, therefore should not be changed-----

        /// <summary>
        /// Provides all devices to the caller.
        /// </summary>
        /// <returns>List of devices</returns>
        public List<Device> GetAllDevices()
        {
            return this.devices;
        }

           

        /// <summary>
        /// Adds a device to the list of devices if unique id is provided.
        /// </summary>
        /// <param name="device">device to be added</param>
        public void AddDevice(Device device)
        {
            foreach (Device dev in this.devices)
            {
                if (dev.Id == device.Id)
                {
                    return;
                }
            }
            devices.Add(device);
        }

        /// <summary>
        /// Provides a device by a given id.
        /// </summary>
        /// <param name="id">the unique identity number of the requested device.</param>
        /// <returns>A device when found, otherwise null</returns>
        public Device GetDeviceById(int id)
        {
            foreach (Device dev in this.devices)
            {
                if (dev.Id == id)
                {
                    return dev;
                }
            }
            return null;
        }

    }
}
