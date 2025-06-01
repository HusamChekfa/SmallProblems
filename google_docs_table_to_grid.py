import requests
from bs4 import BeautifulSoup

def fetch_html(url: str):
    try:
        response = requests.get(url)
        response.raise_for_status()
        return response.text
    except requests.RequestException as e:
        print(f"Error fetching HTML from {url}: {e}")
        return None

def parse_table(soup: BeautifulSoup):
    tables = soup.find_all("table")
    table = tables[0] if tables else None

    if table is None:
        print("No tables found")
        return [], 0, 0

    rows = table.find_all("tr")
    coordinates = []
    max_x = max_y = 0

    for row in rows[1:]:
        columns = row.find_all("td")
        if len(columns) >= 3:
            x = int(columns[0].get_text(strip=True))
            y = int(columns[2].get_text(strip=True))
            symbol = columns[1].get_text(strip=True)

            coordinates.append((x, y, symbol))
            max_x = max(max_x, x)
            max_y = max(max_y, y)

    return coordinates, max_x, max_y

def create_empty_grid(max_x: int, max_y: int):
    return [[' ' for _ in range(max_y + 1)] for _ in range(max_x + 1)]

def fill_grid(grid, coordinates):
    for x, y, symbol in coordinates:
        grid[x][y] = symbol

def print_grid(grid, max_x: int, max_y: int):
    for y in range(max_y, -1, -1):
        row = ''.join(grid[x][y] for x in range(max_x + 1))
        print(row)

def main(url):
    google_docs_data = fetch_html(url)
    if google_docs_data is None:
        return

    soup = BeautifulSoup(google_docs_data, "html.parser")
    coordinates, max_x, max_y = parse_table(soup)

    if not coordinates:
        print("Nothing valid")
        return

    grid = create_empty_grid(max_x, max_y)
    fill_grid(grid, coordinates)

    print_grid(grid, max_x, max_y)

if __name__ == "__main__":
    main("https://docs.google.com/document/d/e/2PACX-1vQGUck9HIFCyezsrBSnmENk5ieJuYwpt7YHYEzeNJkIb9OSDdx-ov2nRNReKQyey-cwJOoEKUhLmN9z/pub")
