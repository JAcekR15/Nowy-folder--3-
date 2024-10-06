import moviepy.editor as mp
import speech_recognition as sr
import os
from pydub import AudioSegment

# Funkcja do konwersji wideo na audio (wav)
def video_to_audio(video_path, audio_output_path):
    video = mp.VideoFileClip(video_path)
    video.audio.write_audiofile(audio_output_path)

# Funkcja do transkrypcji audio do tekstu
def transcribe_audio(audio_path):
    recognizer = sr.Recognizer()
    audio_file = sr.AudioFile(audio_path)
    with audio_file as source:
        audio_data = recognizer.record(source)
    return recognizer.recognize_google(audio_data)

# Funkcja dzielenia wideo na fragmenty
def split_video_on_phrases(video_path, word, segment_length):
    # Tworzenie pliku audio
    audio_path = "temp_audio.wav"
    video_to_audio(video_path, audio_path)
    
    # Transkrypcja dźwięku na tekst
    transcript = transcribe_audio(audio_path)
    
    # Sprawdzenie, gdzie znajduje się dane słowo
    word_positions = []
    words = transcript.split()
    
    for index, w in enumerate(words):
        if word.lower() in w.lower():
            word_positions.append(index)
    
    # Długość jednego fragmentu
    clip_length = segment_length
    
    # Otwórz film wideo
    video = mp.VideoFileClip(video_path)
    
    # Znalezienie czasu wideo na podstawie pozycji słów
    total_duration = video.duration
    words_per_second = len(words) / total_duration
    
    clips = []
    
    for position in word_positions:
        start_time = max(0, position / words_per_second - clip_length / 2)
        end_time = min(total_duration, start_time + clip_length)
        clip = video.subclip(start_time, end_time)
        output_name = f"clip_{position}.mp4"
        clip.write_videofile(output_name)
        clips.append(output_name)
    
    # Usuwanie tymczasowych plików audio
    os.remove(audio_path)
    
    return clips

# Przykład użycia:
video_path = "nazwa_filmu.mp4"
word = "example"  # Wyszukiwane słowo
segment_length = 5  # Długość fragmentów w sekundach

split_video_on_phrases(video_path, word, segment_length)
