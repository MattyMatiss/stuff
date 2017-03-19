using System;
using System.Net;
using System.Net.Http;
using System.Windows;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();
        }

        private void PostButton_Click(object sender, RoutedEventArgs e)
        {
            // create new
        }

        private void PutButton_Click(object sender, RoutedEventArgs e)
        {
            // edit old
        }

        private async void GetNotes_Click(object sender, RoutedEventArgs e)
        {
            // get all as a list

            await DataGetter.GetAllSections();
            SectionsList.ItemsSource = DataGetter.Sections;
        }

        private void SectionsList_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
            if (SectionsList.SelectedItem != null)
            {
                Section sect = (Section)SectionsList.SelectedItem;
                NameTxt.Text = sect.Name;
                DescriptionTxt.Text = sect.Description;
            }
        }
    }

    public class DataGetter
    {
        static private Uri _serverDomain = new Uri($"http://noticeatest.somee.com/");
        static private string _jsonString;
        static private HttpClient _httpClient = new HttpClient();
        static public List<Section> Sections;

        static public async Task GetAllSections()
        {
            var response = await _httpClient.GetAsync(new Uri($"{_serverDomain}api/sections")).ConfigureAwait(false);

            if (response.StatusCode != HttpStatusCode.OK)
                throw new HttpRequestException($"Failed to get notes array [{response.StatusCode}]");

            _jsonString = await response.Content.ReadAsStringAsync();

            Sections = JsonConvert.DeserializeObject<List<Section>>(_jsonString);
        }

        static public async Task PostSection()
        {
            //var response = await _httpClient.PostAsync(new Uri($"{_serverDomain}api/sections")).ConfigureAwait(false);

            //if (response.StatusCode != HttpStatusCode.OK)
            //    throw new HttpRequestException($"Error [{response.StatusCode}]");
        }

        static public async Task PutSection()
        {
            //var response = await _httpClient.PutAsync(new Uri($"{_serverDomain}api/sections")).ConfigureAwait(false);

            //if (response.StatusCode != HttpStatusCode.OK)
            //    throw new HttpRequestException($"Error [{response.StatusCode}]");
        }

    }

    public class Section
    {
        public Section()
        {

        }

        //private int _id;
        //private string _name;
        //private string _content;

        public int Id {
            get;
            set;
        }
        public string Name {
            get;
            set;
        }
        public string Description {
            get;
            set;
        }
        public override string ToString()
        {
            return Name + " (" + Description + ")";
        }
    }
}


