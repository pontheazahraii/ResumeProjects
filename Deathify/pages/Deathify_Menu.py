import streamlit as st
from streamlit_option_menu import option_menu
from Deathify import *
from scraper import *
import pandas as pd 

#Get and display artist info
def getArtistInfo(artist):
    #Name
    artistName = artist[1]
    #Status (Dead/Alive)
    artistStatus = artist[2]
    #Top Song ID
    artistTopSongID = artist[4]
    st.write(artistTopSongID)

    #Gets the name of the top song given its ID
    artistTopSongName = getSongInfo(artistTopSongID)[1]
    #Gets the name of the album the song is in
    artistTopSongAlbumName = getAlbumInfo(artistTopSongID)[1]

    #Outputs artist name on website
    st.write("Artist's name: ", artistName)

    #Outputs artist death status on website
    if (artistStatus == 1):
        st.write("Artist's status: Currently dead")
    else:
        st.write("Artist's status: Currently alive")

    #Outputs top song and its album on website
    st.write(f"Artist's top song: {artistTopSongName} from {artistTopSongAlbumName}")
    
    return artist

#Artist info to use throughout the menu
if "artist" not in st.session_state:
    st.session_state["artist"] = ""

#Creates main page
st.title("Main page")

#Offers options and sets icons for those options from Bootstrap
with st.sidebar:
    option = option_menu(
        menu_title="Deathify Menu",
        options=["Search Artists", "Create Playlist", "Death Verifier", "Sort Songs by Album", "Sort Albums by Artist", 
        "Album Count per Artist", "Display All Artist Information", "Display All Playlists Information", "Change Playlist Name", "Display User's Playlists",
        "Delete a Playlist"],
        icons=["search", "music-note-list", "person-x", "funnel"],
        menu_icon="list",
        orientation="horizontal"
    )

#Search artist option
if option == "Search Artists":
    st.write("You selected the 'Search artist' button")
    userIn = st.text_input("Please enter an artist's name or ID: ")
    if userIn:
        #Get artist info in a tuple
        artist = searchArtist(userIn)
        
        #If artist search didn't come up with anything, try scaping spotify
        #Use JPEGMAFIA as example
        if (None == artist):
            # if(isDead(userIn) == 1):
                
            # else:
            #     getDeathAge(userIn)
            artistID = scrapeSpotify(userIn)
            
            #If artist scraping didn't come up with anything, let user know
            if (-1 == artistID):
                st.write("Couldn't find artist. Please reenter their name/ID. This person may not exist.")
            #Otherwise, insert artist's information into database
            #This may not work all the time because of how info is formatted
            else:
                try:
                    insertArtist(artistID)
                except:
                    deadStatus = st.number_input("Is the artist dead? Type 1 for Yes / Type 0 for No")
                    Dead = int(deadStatus)
                    if(Dead == 1):
                        death = st.number_input("What was the death age of the artist?")
                        DeathAge = int(death)
                    else:
                        currAge = st.number_input("What is the current age of the artist?")
                        currentAge = int(currAge)
                        yearsTill80 = 80 - currentAge 
                        predYearsLeft = random.randint(0,yearsTill80)
                        DeathAge = currentAge + predYearsLeft
                    #dead = ask if artist is dead 
                    # if dead 
                    # age = inputed death age 
                    # else 
                    # age = current age + the code to do the random num selection
                    getArtist = st.button("Get Artist")
                    #If not in session state, create button, which is assigned to true if created and false if not
                    if not st.session_state.get('button'):
                        st.session_state['button'] = getArtist

                    #On button press
                    if st.session_state['button']: 
                        insertArtist(artistID, Dead, DeathAge)

                insertAlbums(artistID)
                insertSongs(artistID)
                getArtistInfo(artist)
                #Save the artist info in session state variable for other buttons to use
                st.session_state["artist"] = artist
        else:
            #Get info about the artist
            getArtistInfo(artist)
            #Save the artist info in session state variable for other buttons to use
            st.session_state["artist"] = artist

#Create playlist option
if option == "Create Playlist":
    st.write(f"You have selected {option}")

    #Create playlist button, must use session states for nested buttons 
    playlistButton = st.button("Create playlist")
    #If not in session state, create button, which is assigned to true if created and false if not
    if not st.session_state.get('button'):
        st.session_state['button'] = playlistButton

    #On button press
    if st.session_state['button']:
        #Load in artist from search
        artist = st.session_state["artist"]

        #ID of artist
        playlistArtistID = artist[0]

        

        #Display playlist that will be made
        st.write("This is the playlist that will be made:")
        df = pd.DataFrame(getPlaylist(playlistArtistID), columns = ['Artist Name', 'Song Name'])
        st.write(df)

        #Nested button is created, on press
        if st.button("Export playlist to csv file"):
            st.download_button("Download",df.to_csv(index = False).encode('utf-8'), "deathify.csv", "text/csv", key='download-csv')

        #Nested button is created, on press
        if st.button("Are you sure you want to make this playlist?"):
            #Get list of top songs given artist ID from the database
            songList = getTopSongs(playlistArtistID)

            #Takes in the ID of artist as well as username and inserts into Playlists table
            insertPlaylist(playlistArtistID, st.session_state["username"])

            #Songs given in individual tuples, converts tuples to strings
            for i in range(len(songList)):
                songList[i] = (songList[i][0])

            #Playlist creation happens here, takes username from session state and loads in list of songs
            st.write("Loading...")
            makePlaylist(st.session_state["username"], songList)
            st.write("Success!")

            #Sets button to false so it can be used again
            st.session_state['button'] = False


#Death verifier option
if option == "Death Verifier":
    st.write(f"You have selected {option}")

    #If artist session state variable not yet set, let user know
    if (0 == len(st.session_state["artist"])):
        st.write("You have not searched an artist yet. Please search artist first.")
    #If artist session state variable set, save into local scope variable
    else:
        artist = st.session_state["artist"]

        #Parse artist info from artist tuple
        artistName = artist[1]
        artistDeathAge = artist[3]
        artistStatus = artist[2]

        #Determine if they're dead, if so display death age
        if (artistStatus == 1):
            st.write(f"The artist {artistName} is dead.")
            st.write(f" {artistName} died when they were {artistDeathAge}.")

        #Determine if they're dead, if not display predicted death age
        else:
            st.write(f"The artist {artistName} is currently alive.")
            st.write(f"According to our algorithm, they will most likely die at {artistDeathAge}.")

if option == "Sort Songs by Album":
    st.write(f"You have selected {option}")
    userIn = st.text_input("Please enter an album's name: ")

    
    #Sorting the songs by Album
    df = pd.DataFrame(sortSongsbyAlbum(userIn), columns = ['Album Name', 'Song Name'])
    st.write(df)

if option == "Sort Albums by Artist":
    st.write(f"You have selected {option}")
    userIn = st.text_input("Please enter an artist's name: ")


    #Sorting the albums by Artist
    df = pd.DataFrame(sortAlbumsbyArtist(userIn), columns = ['Artist Name', 'Album Name'])
    st.write(df)

if option == "Album Count per Artist":
    st.write(f"You have selected {option}")
    userIn = st.text_input("Please enter an artist's name: ")


    #Gets number of albums per artist
    df = pd.DataFrame(AlbumCountPerArtist(userIn), columns = ['Artist Name', 'Album Total'])
    st.write(df)


if option == "Display All Artist Information":
    st.write(f"You have selected {option}")
    userIn = st.text_input("Please enter an artist's name: ")

    #Display all the songs and all the albums given the name of artist
    df = pd.DataFrame(AllArtistInformation(userIn), columns = ['Artist Name', 'Album Name', 'Song Name'])
    st.write(df)

if option == "Display All Playlists Information":
    st.write(f"You have selected {option}")

    #Display all the artists and albums associated with each Playlist
    df = pd.DataFrame(PlaylistInformation(), columns = ['Playlist ID', 'Artist Name', 'Album Name'])
    st.write(df)

if option == "Change Playlist Name":
    st.write(f"You have selected {option}")

    playlistfloat = st.number_input("Please enter a Playlist ID:")
    playlistID = int(playlistfloat)
    newName = st.text_input("Please enter a new Playlist name:")

    #Create playlist button, must use session states for nested buttons 
    playlistNameButton = st.button("Change playlist name")
    #If not in session state, create button, which is assigned to true if created and false if not
    if not st.session_state.get('button'):
        st.session_state['button'] = playlistNameButton
    
    if st.session_state.get('button'):
        prePlaylist = spotifyCreds.user_playlists(user=st.session_state["username"])
        playlist = prePlaylist["items"][playlistID]["id"]

        spotifyCreds.user_playlist_change_details(st.session_state["username"], playlist, name=newName, public=True, description=None)

if option == "Display User's Playlists":
    st.write(f"You have selected {option}")

    #Displaying the artists per each User ID and Playlist ID
    df = pd.DataFrame(DisplayUsersPlaylists(st.session_state["username"]), columns = ['Playlist ID', 'User ID', 'Artist Name'])
    st.write(df)

if option == "Delete a Playlist":
    st.write(f"You have selected {option}")
    Artist = st.text_input("Please enter an artist's name: ")
    playlistfloat = st.number_input("Please enter a Playlist ID:")
    playlistID = int(playlistfloat)

    deleteButton = st.button("Delete Playlist")
    #If not in session state, create button, which is assigned to true if created and false if not
    if not st.session_state.get('button'):
        st.session_state['button'] = deleteButton
    
    if st.session_state.get('button'):
        #Deletes a playlist given the username and artist name
        prePlaylist = spotifyCreds.user_playlists(user=st.session_state["username"])
        playlist = prePlaylist["items"][playlistID]["id"]

        spotifyCreds.user_playlist_unfollow(st.session_state["username"], playlist)
        deletePlaylist(st.session_state["username"], Artist)
