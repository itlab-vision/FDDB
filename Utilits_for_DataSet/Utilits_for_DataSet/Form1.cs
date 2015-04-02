using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
namespace Utilits_for_DataSet
{
    public partial class Form1 : Form
    {

        private StreamWriter file;

        private bool openfile = false;

        private bool clickCountToo = false;

        private List<string> NameImages;

        private List<string> NameDeleteImage;

        private string nameDir;

        private List<PictureBox> image;

        private int iNameImage = 0;

        private PictureBox LastPictureBox ;

        private int count;
        
        private void Click_Image(object sender, EventArgs e)
        {
            LastPictureBox = (PictureBox)sender;
            NameDeleteImage.Add(LastPictureBox.ImageLocation);
            if (iNameImage != NameImages.Count)
            {
                try
                {
                    LastPictureBox.Load(nameDir + NameImages[iNameImage]);
                    iNameImage++;
                    LastPictureBox.Refresh();
                }
                catch
                {
                    NameDeleteImage.Add(nameDir + NameImages[iNameImage]);
                    iNameImage++;
                }

            }
            else
            {
                label1.Text = " end ";
            }

        }

        private void SetImageInForm(int count)
        {
            if (image != null)
            {
                for (int i = 0; i < image.Count; i++)
                {
                    this.Controls.Remove(image[i]);
                }
                image.Clear();
            }
            if (clickCountToo == true) //если количество картинок уже выбиралось и нажали еще раз
            {
                iNameImage = 0;

            }

            if (openfile == true)
            {
                clickCountToo = true; 
                int n = this.Controls.Owner.Width / 150;
                int m = this.Controls.Owner.Height / 150;

                int k = 1;
                int l = 0;
                image = new List<PictureBox>();
                for (int i = 0; i < count; i++)
                {
                    image.Add( new PictureBox());
                    image[i].SizeMode = PictureBoxSizeMode.StretchImage;
                    image[i].Width = 150;
                    image[i].Height = 150;

                    if (i == n * k)
                    {
                        k++;
                        l = 0;
                    }

                    if (this.Controls.Owner.Height - (20 + 150 * (k - 1)) >= 150)
                    {
                        image[i].Location = new Point(l * 150, 20 + 150 * (k - 1));

                        image[i].Click += new EventHandler(Click_Image);

                        l++;
                        image[i].Load(nameDir + NameImages[iNameImage]);
                        iNameImage++;
                        this.Controls.Add(image[i]);

                    }
                    else
                        break;

                }
            }
        }

        private void CreateListName(string name)
        {

            string[] line = File.ReadAllLines(name);

            string[] str;

            for (int i = 0; i < line.Length; i++)
            {
                if (line[i] != "")
                {
                    str = line[i].Split(' ');
                    if ((str[0]!="") || (str[0]!="\n"))
                        NameImages.Add(str[0]);
                }
            }


        }

        public Form1()
        {
            InitializeComponent();
            
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {


            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    label.Text = "";
                    label1.Text = "";
                    NameImages = new List<string>();
                    NameDeleteImage = new List<string>();
                    CreateListName(openFileDialog.FileName);
                    nameDir = openFileDialog.FileName.Substring(0, openFileDialog.FileName.Length - openFileDialog.SafeFileName.Length-47);                   
                    openfile = true;
                }
                catch
                { 
                    label.Text = "file isn't open. try again"; 
                }
                
            }

        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string[] line = File.ReadAllLines(openFileDialog.FileName);
            string[] newLine = new string[line.Length];
            string [] p ;
            bool flag = true;
            var str = "";
            for (int i = 0; i < line.Length; i++)
            {
                for (int j = 0; j < NameDeleteImage.Count; j++)
                {
                    p = line[i].Split(' ');
                    str = nameDir + p[0];
                    if (str == NameDeleteImage[j])
                    {
                        flag = false;
                    }
                }

                if (flag)
                {
                    newLine[i] = line[i];
                }

                flag = true;
            }

            File.WriteAllLines("new_annotatin.txt", newLine);
            if (Form1.ActiveForm != null)
            {
                Form1.ActiveForm.Close();
            }
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            SetImageInForm(20);
            count = 20;
           
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            SetImageInForm(40);
            count =40;

        }

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            count = 60;
            SetImageInForm(60);
        }

        private void toolStripMenuItem5_Click(object sender, EventArgs e)
        {
            count = 80;
            SetImageInForm(80);
        }

        private void toolStripMenuItem6_Click(object sender, EventArgs e)
        {
            count = 100;
            SetImageInForm(100);
        } 
        
        private void toolStripMenuItem7_Click(object sender, EventArgs e)
        {
            count = 50;
            SetImageInForm(50);
        }

        private void отметитьToolStripMenuItem_Click(object sender, EventArgs e)
        {

            if (LastPictureBox != null)
            {
                LastPictureBox.Load(NameDeleteImage[NameDeleteImage.Count - 1]);
                iNameImage--;
                LastPictureBox.Refresh();

                NameDeleteImage.RemoveAt(NameDeleteImage.Count - 1);
            }
        }

        private void показатьСледующиеИзображенияToolStripMenuItem_Click(object sender, EventArgs e)
        {

            if (openfile == true)
            {
                for (int i = 0; i < image.Count; i++)
                {
                    if (iNameImage != NameImages.Count)
                    {
                        try
                        {
                            image[i].Load(nameDir + NameImages[iNameImage]);
                            iNameImage++;
                            this.Controls.Add(image[i]);
                        }
                        catch
                        {
                            NameDeleteImage.Add(nameDir + NameImages[iNameImage]);
                            iNameImage++;                            
                        }


                    }
                    else
                    {
                        label1.Text = " end ";
                    }

                }
            }

        }

        private void удавитьТекущийСписокToolStripMenuItem_Click(object sender, EventArgs e)
        {


            string[] line = File.ReadAllLines(openFileDialog.FileName);
            string[] newLine = new string[line.Length];
            string[] p;
            bool flag = true;
            var str = "";
            for (int i = 0; i < line.Length; i++)
            {
                for (int j = 0; j < NameDeleteImage.Count; j++)
                {
                    p = line[i].Split(' ');
                    str = nameDir + p[0];
                    if (str == NameDeleteImage[j])
                    {
                        flag = false;
                    }
                }

                if (flag)
                {
                    newLine[i] = line[i];
                }

                flag = true;
            }

            File.WriteAllLines("new_annotatin.txt", newLine);        
        }

        private void соъраитьСписокФайловToolStripMenuItem_Click(object sender, EventArgs e)
        {
            using (file = new StreamWriter("rotated_persons.txt"))
            {
                for (int i = 0; i < NameDeleteImage.Count; i++)
                {
                    file.Write(NameDeleteImage[i]  + Environment.NewLine);
                }
            }

        }

    }
}
