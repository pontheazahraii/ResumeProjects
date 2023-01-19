import mysql.connector
import spotipy
from spotipy.oauth2 import SpotifyClientCredentials
from spotipy.oauth2 import SpotifyOAuth
import time
from dotenv import load_dotenv
from lyricsgenius import Genius
import os
from datetime import date 
import random 
import streamlit as st

#---------------------------------------------SET UP---------------------------------------------

load_dotenv() #loads env vars

#Retrieves credentials
clientID = os.environ['SPOTIPY_CLIENT_ID']
clientSecret = os.environ['SPOTIPY_CLIENT_SECRET']
redirctURI = os.environ['SPOTIPY_REDIRECT_URI']
scope = "playlist-modify-public, playlist-modify-private, user-library-read, user-top-read"
spotifyCreds = spotipy.Spotify(auth_manager=SpotifyOAuth(scope=scope))

geniusCreds = Genius(access_token=os.environ['access_token'])

#Connects to sql
mydb = mysql.connector.connect(host = "localhost",
        user = "root",
        password = "Zahraii2366637.",
        auth_plugin = 'mysql_native_password',
        database = "Deathify")
print(mydb)

mycursor = mydb.cursor()

#Sets up streamlit page 
st.set_page_config(
    page_title="Deathify Login"
)

st.title("Login Page")
if "username" not in st.session_state:
    st.session_state["username"] = ""

#---------------------------------------------HELPER FUNCTIONS---------------------------------------------
# '''
# This method fetches all queries
# Parameters: 
# - query: the query to fetch 
# Returns: 
# - record: the fetched records
# '''
def fetchall(query):
    mycursor.reset()
    mycursor.execute(query)
    record = mycursor.fetchall()
    return record

# '''
# This method fetches a query 
# Parameters: 
# - query: the query to fetch 
# Returns: 
# - record: the fetched record 
# '''
def fetch(query):
    mycursor.reset()
    mycursor.execute(query)
    record = mycursor.fetchone()
    return record

# '''
# This method executes a query 
# Parameters: 
# - query: the query to execute 
# '''
def execute(query):
    mycursor.reset()
    mycursor.execute(query)
    mydb.commit()

#---------------------------------------------ACCESSORS AND MUTATORS---------------------------------------------
# '''
# This method is the accessor for an artists name 
# Parameters: 
# - artistID: the ID of the artist 
# Returns: 
# - the name of the artist 
# '''
def getArtistName(artistID):
    print("Get Artist Name")
    return spotifyCreds.artist(artistID)['name']

# '''
# This method is the accessor for the top song of an artist 
# Parameters: 
# - artistID: the ID of the artist 
# Returns: 
# - the ID of the top song of the artist 
# '''
def getTopSongID(artistID):
    print("Get Top Song ID")
    return spotifyCreds.artist_top_tracks(artistID, country='US')['tracks'][0]['id']

# '''
# This method is the accessor for an artists albums 
# Parameters: 
# - artistID: the ID of the artist 
# Returns: 
# -  a list of all of an artists album's IDs 
# '''
def getAlbumIDs(artistID):
    print("Get AlbumIDs")
    albums = spotifyCreds.artist_albums(artistID, album_type='album')['items']
    albumIDs = []
    for i in range(0,len(albums)):
        albumID = albums[i]['id']
        albumIDs.append(albumID)
    return albumIDs

# '''
# This method is the accessor for the titles of an album 
# Parameters: 
# - albumID: the ID of the album  
# Returns: 
# - the name of the album 
# '''
def getAlbumTitle(albumID):
    print("Get Album Title")
    return spotifyCreds.album(albumID)['name']

# '''
# This method is the accessor for the total number of tracks in an album 
# Parameters: 
# - albumID: the ID of the album 
# Returns: 
# - the total number of tracks in an album 
# '''
def getAlbumTotalTracks(albumID):
    print("Get Album Total Tracks")
    return spotifyCreds.album(albumID)['total_tracks']

# '''
# This method is the accessor for the IDs of the songs on an album 
# Parameters: 
# - albumID: the ID of the album 
# Returns: 
# - a list of IDs of songs that are on an album 
# '''
def getSongIDs(albumID):
    print("Get SongIDs")
    songs = spotifyCreds.album(albumID)['tracks']['items']
    songIDs = []
    for i in range(0, len(songs)):
        songID = songs[i]['id']
        songIDs.append(songID)
    return songIDs

# '''
# This method is the accessor for the name of a song
# Parameters: 
# - songID: the ID of the song
# Returns: 
# - the name of the song  
# '''
def getSongName(songID):
    print("Get Song Name")
    return spotifyCreds.track(songID)['name']

# '''
# This method is the accessor for the ID of a user 
# Parameters: 
# - userLink: the link to the users spotify user page 
# Returns: 
# - the ID of the user 
# '''
def getUserID(userLink): 
    userID = userLink.split('/')[-1].split('?')[-2]
    return userID

# '''
# This method is the accessor for the dates of an artists birth and death
# Parameters: 
# - name: the name of the artist 
# Returns: 
# - the birth and death dates of an artist 
# '''
def getDates(name):
    print("Get Dates")
    artistID = geniusCreds.search(name,type_="artist")['sections'][0]['hits'][0]['result']['id']
    description = geniusCreds.artist(artistID)['artist']['description']['plain']
    return description[description.find('(')+1:description.find(')')]

# '''
# This method is the accessor for the death age of an artist
# If the artist is dead the real age of the artist will be extracted
# If the artist is alive a death age will be predicted for the artist 
# Parameters: 
# - name: The name of the artist 
# Returns: 
# - the death age of the artist 
# '''
def getDeathAge(name):
    try: 
        print("Get Death Age")
        dates = getDates(name)
        birth = {"January" : 1, 
            "February": 2,
            "March": 3, 
            "April": 4,
            "May": 5,
            "June": 6,
            "July": 7, 
            "August": 8,
            "September": 9,
            "October": 10,
            "November": 11,
            "December": 12}

        dates = dates.split(" ")
        
        str_lst = []
        # for all the values in the dates 
        for x in range(0,len(dates)):
            # change the month to it's numeric value 
            if dates[x] in birth:
                dates[x] = birth[dates[x]]
            # strip non digits from the values 
            elif "," in dates[x]:
                day = ""
                for char in dates[x]:
                    if char.isdigit():
                        day += char
                dates[x] = int(day)
            # change all digit values to integers 
            elif dates[x].isdigit():
                dates[x] = int(dates[x])
            # add non-date values to the list 
            else: 
                str_lst.append(x)

        # remove non-date values from the list of dates 
        if not len(str_lst) == 0:
            for x in range(0,len(str_lst)):
                dates.pop(str_lst[x])

        # convert to a date object 
        birthDate = date(dates[2], dates[0], dates[1])
        # if the artist is dead, find their age based on their death age 
        if isDead(name) == 1:
            deathDate = date(dates[5], dates[3], dates[4])
            age = deathDate.year - birthDate.year - ((deathDate.month, deathDate.day) < (birthDate.month, birthDate.day))
        # if the artist is alive, predict their death age using a random num generator 
        else:
            today = date.today()
            currAge = today.year - birthDate.year - ((today.month, today.day) < (birthDate.month, birthDate.day))
            yearsTill80 = 80 - currAge 
            predYearsLeft = random.randint(0,yearsTill80)
            age = currAge + predYearsLeft
        
        return age
    except: 
        return 0

# '''
# This method is the mutator for an artist record
# Parameters: 
# - artistID: the ID of the artist 
# Returns: 
# - all the information of an artist 
# '''
def setArtist(artistID):
    print("Set Artist")
    name = getArtistName(artistID)

    artist = {'ArtistID': artistID,
    'Name': name.replace("'", "''"),
    'Dead': int(isDead(name)),
    'DeathAge': int(getDeathAge(name)),
    'TopSongID': getTopSongID(artistID)}

    return artist

def setArtist(artistID, Dead, DeathAge):
    print("Set Artist")
    name = getArtistName(artistID)

    artist = {'ArtistID': artistID,
    'Name': name.replace("'", "''"),
    'Dead': Dead,
    'DeathAge': DeathAge,
    'TopSongID': getTopSongID(artistID)}

    return artist

# '''
# This method is the mutator for all the records for an artists albums 
# Parameters: 
# - artistID: the ID of an artist
# Returns: 
# - all the information of all the albums of an artist 
# '''
def setAlbums(artistID):
    print("Set Albums")
    albumIDs = getAlbumIDs(artistID)
    albums = []

    for albumID in albumIDs:
        album = {'AlbumID': albumID,
        'Title': getAlbumTitle(albumID).replace("'", "''"),
        'TotalTracks': int(getAlbumTotalTracks(albumID)),
        'ArtistID': artistID}

        albums.append(album)

    return albums

# '''
# This method is the mutator for all the records for an albums songs
# Parameters: 
# - albumsID: the ID of the album
# Returns: 
# - all the information of all the songs on an album 
# '''
def setSongs(albumID):
    print("Set Albums")
    songIDs = getSongIDs(albumID)
    songs = []

    for songID in songIDs:
        song = {"SongID": songID,
        "Name": getSongName(songID).replace("'", "''"),
        "AlbumID": albumID}

        songs.append(song)

    return songs

# '''
# This method returns if the artist is dead or not 
# Parameters: 
# - name: the of the artist 
# Returns: 
# - whether the artist is dead or not 
# '''
def isDead(name):
    print("Is Dead")
    if '–' in getDates(name):
        return 1
    else:
        return 0
        
#---------------------------------------------SQL COMMANDS---------------------------------------------
# ''' This method creates all the tables for the Deathify database '''
def createTables():
    query = '''
    CREATE TABLE Albums(
        AlbumID VARCHAR(200) PRIMARY KEY,
        Title VARCHAR(200),
        TotalTracks INT, 
        ArtistID VARCHAR(200)
    );
    '''
    execute(query)

    query = '''
    CREATE TABLE Artists(
        ArtistID VARCHAR(200) PRIMARY KEY,
        Name VARCHAR(200),
        Dead TINYINT(1), 
        DeathAge INT,
        TopSongID VARCHAR(200)
    );
    '''
    execute(query)

    query = '''
    CREATE TABLE Songs(
        SongID VARCHAR(200) PRIMARY KEY,
        Name VARCHAR(200),
        AlbumID VARCHAR(200)
    );
    '''
    execute(query)

    query = '''
    CREATE TABLE UserPlaylist(
        UserID VARCHAR(200),
        PlaylistID INT,
        FOREIGN KEY (UserID) REFERENCES Users (UserID),
        FOREIGN KEY (PlaylistID) REFERENCES Playlists(PlaylistID)
    );
    '''
    execute(query)

    query = '''
    CREATE TABLE Playlists(
        PlaylistID INTEGER NOT NULL AUTO_INCREMENT PRIMARY KEY,
        ArtistID VARCHAR(200),
        UserID VARCHAR(200)
    );
    '''
    execute(query)

    query = '''
    CREATE TABLE Users(
        UserID INT NOT NULL AUTO_INCREMENET PRIMARY KEY,
        Username VARCHAR(200),
        Password VARCHAR(200)
    );
    '''
    execute(query)

    query = '''
    CREATE VIEW DisplayUsersPlaylists AS
    SELECT u.UserID, pl.PlaylistID, a.Name
    FROM Users AS u INNER JOIN Playlists AS pl
    ON u.Username = pl.UserID
    INNER JOIN Artists AS a
    ON pl.ArtistID = a.ArtistID
    WHERE u.Username = '%s'
    GROUP BY pl.PlaylistID, u.UserID;    
    # '''%(userID)

    execute(query)

    

# ''' 
# The method inserts an artist in the my sql database 
# Parameters: 
# - artistID: the ID of the artist 
# '''
def insertArtist(artistID):
    print("Insert Artist")
    artist = setArtist(artistID)
    query = '''
    INSERT INTO Artists (ArtistID, Name, Dead, DeathAge, TopSongID)
    VALUES ('%s', '%s', '%s', '%s', '%s');
    ''' % (artist['ArtistID'], artist['Name'], artist['Dead'], artist['DeathAge'], artist['TopSongID'])
    print(query)
    execute(query)
    print("Inserted Artist")

def insertArtist(artistID, Dead, DeathAge):
    print("Insert Artist")
    artist = setArtist(artistID, Dead, DeathAge)
    query = '''
    INSERT INTO Artists (ArtistID, Name, Dead, DeathAge, TopSongID)
    VALUES ('%s', '%s', '%s', '%s', '%s');
    ''' % (artist['ArtistID'], artist['Name'], artist['Dead'], artist['DeathAge'], artist['TopSongID'])
    print(query)
    execute(query)
    print("Inserted Artist")

# ''' 
# The method to insert all of an artists albums into the mysql database 
# Parameters: 
# - artistID: the ID of the artist 
# '''
def insertAlbums(artistID):
    print("Insert Albums")
    albums = setAlbums(artistID)
    for album in albums:
        query = '''
        INSERT INTO Albums (AlbumID, Title, TotalTracks, ArtistID)
        VALUES ('%s', '%s', '%s', '%s');
        ''' % (album['AlbumID'], album['Title'], album['TotalTracks'], album['ArtistID'])
        execute(query)
    print("Inserted Albums")

# ''' 
# The method to insert all songs of an artist into the mysql database
# Parameters: 
# - artistID: the ID of the artist 
# '''
def insertSongs(artistID):
    print("Insert Songs")
    albums = setAlbums(artistID)
    albumIDs = []

    for album in albums:
        albumIDs.append(album['AlbumID'])

    for albumID in albumIDs:
        songs = setSongs(albumID)
        for song in songs:
            query = '''
            INSERT INTO Songs (SongID, Name, AlbumID)
            VALUES ('%s', '%s', '%s');
            ''' % (song['SongID'], song['Name'], song['AlbumID'])
            execute(query)
    print("Inserted Songs")

# ''' 
# The method to insert all playlist information into the mysql database
# Parameters: 
# - artistID: the ID of the artist 
# - userLink: the spotify link of the user
# '''
def insertPlaylist(artistID, userID):
    #userID = getUserID(userLink)
    query = '''
    INSERT INTO Playlists (ArtistID, UserID)
    VALUES ('%s', '%s');
    ''' % (artistID, userID)
    execute(query)
    

def insertUserPlaylist(userID, playlistID):
    query = '''
    INSERT INTO UserPlaylist (UserID, PlaylistID)
    VALUES ('%s', '%s'); 
    ''' % (userID, playlistID)
    execute(query)

def insertUsers(username):
    query = '''
    INSERT INTO Users (Username)
    VALUES ('%s'); 
    ''' % (username)
    execute(query)
    

def deletePlaylist(userID, artistName):
    artistID = getArtistID(artistName)
    query = '''
    DELETE FROM Playlists
    WHERE ArtistID = '%s' 
    AND UserID = '%s'; 
    ''' % (artistID, userID)

    execute(query)


def getArtistID(artistName):
    query = '''
    SELECT ArtistID
    FROM Artists
    WHERE Name = '%s'; 
    ''' % (artistName)

    return fetch(query)[0]
# ''' 
# The method to get a playlist with names of the artists based on death age from the mysql database
# Parameters: 
# - artistID: the ID of the artist 
# '''
def getPlaylist(artistID):
    deathAge = getDeath(artistID)
    query = '''
    SELECT a.Name AS ArtistName, s.Name AS SongName
    FROM Artists AS a
    INNER JOIN Songs AS s
    ON a.TopSongID = s.SongID
    WHERE a.DeathAge = '%s'; 
    ''' %(deathAge)

    return fetchall(query)

# ''' 
# The method to get the song IDs for the playlist based on death age from the mysql database
# Parameters: 
# - artistID: the ID of the artist 
# '''
def getTopSongs(artistID):
    deathAge = getDeath(artistID)
    query = '''
    SELECT TopSongID
    FROM Artists
    WHERE DeathAge = '%s'; 
    ''' %(deathAge)

    return fetchall(query)

# ''' 
# The method to get the death age from the mysql database
# Parameters: 
# - artistID: the ID of the artist 
# '''
def getDeath(artistID):
    query = '''
    SELECT DeathAge
    FROM Artists
    WHERE ArtistID = '%s'
    ''' %(artistID)

    return fetch(query)[0]

# ''' 
# Search for and return the info of a particular song given the song ID 
# Parameters: 
# - songID: the ID of the song 
# '''
def getSongInfo(songID):
    querySearch = '''
    SELECT DISTINCT *
    FROM Songs
    WHERE SongID = '%s';
    ''' %(songID)
    return fetch(querySearch)

# ''' 
# Search for and return album info of the song it belongs to given the song ID 
# Parameters: 
# - songID: the ID of the song 
# Returns: 
# - the information of an album 
# '''
def getAlbumInfo(songID):
    querySearch = '''
    SELECT DISTINCT *
    FROM Albums
    WHERE AlbumID = '%s'
    ''' %(getSongInfo(songID)[2]) #Gets tuple containing song info and extracts associated albumID
    return fetch(querySearch)

# ''' 
# Search for and return the info of a particular artist given the artist ID 
# Parameters: 
# - artistID: the ID of the artist 
# Returns 
# - the information of an artist 
# '''
def getArtist(artistID):
    # We tend to return duplicate of the same information, so I'll use DISTINCT * instead of just *
    querySearch = '''
    SELECT DISTINCT *
    FROM Artists
    WHERE ArtistID = '%s'
    ''' %(artistID)
    return fetch(querySearch)

# ''' 
# Overloads other method to ensure artist will be found regardless if fed artist ID or name 
# Parameters: 
# - artistName: the name of the artist 
# Returns: 
# - the information of an artist 
# '''
def searchArtist(artistName):
    queryDisplay = '''
    SELECT DISTINCT *
    FROM Artists
    WHERE Name = '%s'
    '''%(artistName)

    # queryIndex = '''
    # CREATE INDEX artistIndex
    # ON Artists (Name);
    # '''

    # execute(queryIndex)
    
    return fetch(queryDisplay)

# ''' 
# Display the total number of artists in the Artist table 
# Returns: 
# - The total number of artists in the Artist table 
# '''
def getAllArtists():
    queryAll = '''
    SELECT COUNT(*)
    FROM Artists
    '''
    return fetch(queryAll)

# ''' 
# Check if artist exists within the Artist table given the artist ID
# Parameters: 
# - artistID: the ID of the artist 
# Returns: 
# - if the artist is in the database or not 
# '''
def checkArtistExist(artistID):
    query = '''
    SELECT COUNT('%s')
    FROM Artists
    ''' %(artistID)

    Count = fetch(query)[0]

    if(Count >= 1):
        return 1
    else: 
        return 0

# ''' 
# Checks if artist is dead given the name of artist 
# Parameters: 
# - artistName: the name of the artist 
# Returns: 
# - if the artist is dead 
# '''
def checkArtistDead(artistName):
    query = '''
    SELECT * 
    FROM Artists
    WHERE Name = '%s'
    '''%(artistName)
    return fetch(query)[0]

# ''' 
# predicts the death of the artist 
# Parameters: 
# - artistName: the name of the artist 
# Returns: 
# - the predicted death age of the artist 
# '''
def predictArtistDeath(artistName):
    DeathAge = str(getDeathAge(artistName))

    # Might change this query to display all artist information instead of just ArtistID
    queryID = '''       
    SELECT ArtistID
    FROM Artists
    WHERE Name = '%s'
    '''%(artistName)

    artistID = fetch(queryID)[0]
    print("The predicted death age of " + artistName + " is " + DeathAge)

# ''' Sorted albums by each Artist in descending order '''
def sortAlbumsbyArtist(artistName):
    query = '''
    SELECT a.Name AS ArtistName, al.Title AS AlbumTitle
    FROM Artists AS a
    INNER JOIN Albums AS al
    ON a.ArtistID = al.ArtistID
    WHERE a.Name = '%s'
    ORDER BY al.Title;
    '''%(artistName)
    return fetchall(query)

# ''' Sorted songs by each album in descending order '''
def sortSongsbyAlbum(albumName):
    query = '''
    SELECT al.Title AS AlbumTitle, s.Name AS SongName
    FROM Albums AS al
    INNER JOIN Songs AS s
    ON al.AlbumID = s.AlbumID
    WHERE al.Title = '%s'
    ORDER BY s.Name;
    '''%(albumName)
    return fetchall(query)

# ''' Sorted songs by each playlist in descending order (CANNED)'''
# def sortSongsbyPlaylists():
#     query = '''
#     SELECT pl.PlaylistID, s.Name
#     FROM Playlists AS pl INNER JOIN Artists AS a
#     ON pl.ArtistID = a.ArtistID
#     INNER JOIN Albums AS al
#     ON a.AlbumID = al.AlbumID
#     INNER JOIN Songs AS s
#     ON al.AlbumID = s.AlbumID
#     GROUP BY pl.PlaylistID
#     ORDER BY pl.PlaylistID

#     '''
#     return fetchall(query)


# ''' Uses a SELECT subquery to display the name of Artist as well as number of their produced Albums '''
def AlbumCountPerArtist(artistName):
    query = '''
    SELECT Name, (SELECT COUNT(*)
                    FROM Albums
                    WHERE Artists.ArtistID = Albums.ArtistID)
    FROM Artists
    WHERE Name = '%s';
    '''%(artistName)
    return fetchall(query)

# '''Joins Artists, Albums, and Songs tables to display each respectively in associated with a given artist name '''
def AllArtistInformation(artistName):
    query = '''
    SELECT a.Name, al.Title, s.Name
    FROM Artists AS a INNER JOIN Albums AS al
    ON a.ArtistID = al.ArtistID
    INNER JOIN Songs AS s
    ON al.AlbumID = s.AlbumID
    WHERE a.Name = '%s';
    '''%(artistName)

    return fetchall(query)

# '''Joins Playlists, Artists, and Albums tables to display the information from each respective playlist'''
def PlaylistInformation():
    query = '''
    SELECT pl.PlaylistID, a.Name, al.Title
    FROM Playlists AS pl INNER JOIN Artists AS a
    ON pl.ArtistID = a.ArtistID
    INNER JOIN Albums AS al
    ON a.ArtistID = al.ArtistID
    GROUP BY pl.PlaylistID;
    '''

    return fetchall(query)

# ''' Displays all information provided by the view created in the tables section '''
def CreateView(userID):
    query = '''
    CREATE VIEW DisplayUsersPlaylists AS
    SELECT u.UserID, pl.PlaylistID, a.Name
    FROM Users AS u INNER JOIN Playlists AS pl
    ON u.Username = pl.UserID
    INNER JOIN Artists AS a
    ON pl.ArtistID = a.ArtistID
    WHERE u.Username = '%s'
    GROUP BY pl.PlaylistID, u.UserID;    
    # '''%(userID)

    execute(query)

def DisplayUsersPlaylists(userID):
    try:
        CreateView(userID)
        queryDisplay ='''
        SELECT *
        FROM DisplayUsersPlaylists;
        '''
    except:
        queryDisplay ='''
        SELECT *
        FROM DisplayUsersPlaylists;
        '''

    return fetchall(queryDisplay)

#---------------------------------------------METHODS---------------------------------------------
# '''
# This method populates the database
# Parameters: 
# - file: the file to read from 
# '''
def populateTables(file):
    fin = open(file, 'r')
    artistIDs = fin.readlines()
    fout = open("failed.txt", 'a')

    for artistID in artistIDs:
        try: 
            artistID = str(artistID.strip())
            insertArtist(artistID)
            time.sleep(1)
            insertAlbums(artistID)
            time.sleep(1)
            insertSongs(artistID)
            time.sleep(1)
        except Exception: 
            print(artistID, file=fout)

    fin.close()
    fout.close()

def makePlaylist(username, songList):
    playlistName = "death playlist"
    playlistDescription = "if this works we buy cake version 2"
    spotifyCreds.user_playlist_create(user=username,name=playlistName,public=True,description=playlistDescription)

    prePlaylist = spotifyCreds.user_playlists(user=username)
    playlist = prePlaylist["items"][0]["id"]

    spotifyCreds.playlist_add_items(playlist_id=playlist,items=songList)


#---------------------------------------------MAIN---------------------------------------------
# ''' The main method '''
def main():
    # userID = getUserID("https://open.spotify.com/user/oq1itahcink0pxu7qo06d8tyj?si=95cc8a368916496d")
    #sortSongsbyAlbum()
    
    # print(searchArtist(getArtistName("https://api.spotify.com/v1/artist/4MCBfE4596Uoi2O4DtmEMz")))

    
    
    st.title("Welcome to deathify!")
    # Get user's login credentials
    username = st.text_input("Enter your username:")
    # password = st.text_input("Enter your password:", type="password")
    if st.button("Login"):
        st.write("Login successful!")
        st.session_state["username"] = username
        insertUsers(st.session_state["username"])


    



    # fin = open("artistID.txt","r")
    # lines = fin.readlines()
    # fout1 = open("exists.txt", "a")
    # fout2 = open("dne.txt", "a")
    # for line in lines:
    #     try:
    #         isDead(getArtistName(line))
    #         print(line, file=fout1)
    #     except Exception: 
    #         print(line, file=fout2)
    # fin.close()
    # fout1.close()
    # fout2.close()
    # populateTables('artistID.txt')

if __name__ == "__main__":
	main()