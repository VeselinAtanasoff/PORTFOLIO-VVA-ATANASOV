using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PoloClubApp
{
    public partial class PoloClubAppForm : Form
    {

        // Provide your answers here
        

        private void btnViewAllWearables_Click(object sender, EventArgs e)
        {
            lbOverview.Items.Clear();   
            List<Device> wearables = myClub.GetWearables();
            foreach (Device dev in wearables)
            {
                lbOverview.Items.Add(dev.GetDetails());
            }
        }

        private void btnAssign_Click(object sender, EventArgs e)
        {
            object selectedDevice = cbDevice.SelectedItem;
            if(selectedDevice == null)
            {
                MessageBox.Show("Please select a device");
                return;
            }
            if(tbPlayerName.Text == "")
            {
                MessageBox.Show("Please enter a player name");
                return;
            }

            int deviceId = Convert.ToInt32(selectedDevice);
            myClub.AssignDevice(deviceId, tbPlayerName.Text, myClub);
            MessageBox.Show("Device assigned if it is not previously assigned");
            tbPlayerName.Text = "";
            
        }

        private void btnReturn_Click(object sender, EventArgs e)
        {
            object selectedDevice = cbDevice.SelectedItem;
            if(selectedDevice == null)
            {
                MessageBox.Show("Please select a device");
                return;
            }

            int deviceId = Convert.ToInt32(selectedDevice);
            if (myClub.ReturnDevice(deviceId, myClub))
            {
                MessageBox.Show("Device returned");
            }
            else
            {
                MessageBox.Show("Device is not assigned to a player");
            }
            tbPlayerName.Text = "";
        }

        private void btnShowAssignedDevices_Click(object sender, EventArgs e)
        {
            lbOverview.Items.Clear();
            foreach (Device dev in myClub.GetAllDevices())
            {
                if (dev.playerName != null)
                {
                    lbOverview.Items.Add(dev.GetDetails());
                }
            }
        }


        private void btnGeneratePlayerTextReport_Click(object sender, EventArgs e)
        {
            lbOverview.Items.Clear();
            string name = tbPlayerNameForFile.Text;
            if (name == "")
            {
                MessageBox.Show("Please enter a player name");
                return;
            }
            
            string report=myClub.GenerateReportPerPlayer(name);
            string[] lines = report.Split(new string[] { "\n" }, StringSplitOptions.None);
            foreach (string line in lines)
            {
                lbOverview.Items.Add(line);
            }
            

        }



        // -----The provided code below will not be graded, therefore should not be changed-----

        private Club myClub;
        public PoloClubAppForm()
        {
            InitializeComponent();
            myClub = new Club("Polo Koningen - powered by Veselin Atanasov");
            this.Text = myClub.Name;
            this.addSomeTestingStuff();
            this.fillComboBoxDevices();
        }

        private void addSomeTestingStuff()
        {
            myClub.AddDevice(new SmartPhone(101, "iPhone X"));
            myClub.AddDevice(new SmartWatch(202, "Apple Watch Sport", 5, 38));
            myClub.AddDevice(new FitTracker(300, "Fitbit Ionic", 1, "pink"));
            myClub.AddDevice(new SmartWatch(203, "Motorola Moto 360", 9, 40));
            myClub.AddDevice(new SmartPhone(102, "iPhone 9"));
            myClub.AddDevice(new SmartPhone(103, "Galaxy S9"));
            myClub.AddDevice(new FitTracker(301, "Fitbit Alta HR", 8, "blue"));
            myClub.AddDevice(new SmartPhone(104, "Pixels 2"));
            myClub.AddDevice(new SmartWatch(204, "Samsung Gear Sport", 2, 42));
            myClub.AddDevice(new FitTracker(302, "Fitbit Charge 2", 10, "black"));
            myClub.AddDevice(new FitTracker(303, "Misfit Ray", 0, "black"));

        }
        private void fillComboBoxDevices()
        {
            foreach (Device dev in myClub.GetAllDevices())
            {
                cbDevice.Items.Add(dev.Id);
            }
        }

        private void btnViewAllDevices_Click(object sender, EventArgs e)
        {
            this.lbOverview.Items.Clear();
            foreach (Device dev in myClub.GetAllDevices())
            {
                this.lbOverview.Items.Add(dev.GetDetails());
            }
            tbPlayerNameForFile.Text = "";
        }


    }
}
