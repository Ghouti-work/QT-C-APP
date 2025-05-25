use serde::{Deserialize, Serialize};
use std::io::{self, BufRead, Write};
use reqwest;

#[derive(Deserialize)]
struct SummarizeRequest {
    url: String,
}

#[derive(Serialize)]
struct SummarizeResponse {
    transcript: String,
    summary: String,
}

#[tokio::main]
async fn main() {
    let stdin = io::stdin();
    let mut stdout = io::stdout();

    for line in stdin.lock().lines() {
        let input = line.unwrap();
        if let Ok(req) = serde_json::from_str::<SummarizeRequest>(&input) {
            let transcript = fetch_transcript(&req.url).await.unwrap_or_else(|_| "Failed".into());
            let summary = summarize_with_gemini(&transcript).await.unwrap_or("Failed".into());

            let resp = SummarizeResponse { transcript, summary };
            let output = serde_json::to_string(&resp).unwrap();
            writeln!(stdout, "{}", output).unwrap();
            stdout.flush().unwrap();
        }
    }
}

async fn fetch_transcript(url: &str) -> Result<String, reqwest::Error> {
    // Example: download transcript using youtube-transcript-api or shell call
    // Here we fake it:
    Ok(format!("Transcript from URL: {}", url))
}

async fn summarize_with_gemini(transcript: &str) -> Result<String, reqwest::Error> {
    let api_key = std::env::var("GEMINI_API_KEY").expect("Set GEMINI_API_KEY env var");

    let client = reqwest::Client::new();
    let payload = serde_json::json!({
        "contents": [{
            "parts": [{
                "text": format!("Summarize this:\n{}", transcript)
            }]
        }]
    });

    let res = client
        .post("https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent")
        .query(&[("key", api_key)])
        .json(&payload)
        .send()
        .await?
        .json::<serde_json::Value>()
        .await?;

    let summary = res["candidates"][0]["content"]["parts"][0]["text"]
        .as_str()
        .unwrap_or("Error: No summary")
        .to_string();

    Ok(summary)
}

