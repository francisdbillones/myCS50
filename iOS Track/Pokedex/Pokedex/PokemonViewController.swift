import UIKit

class PokemonViewController: UIViewController {
    var url: String!
    var isCaught: Bool!

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var image: UIImageView!
    @IBOutlet var pokemonDescription: UILabel!
    
    var result: PokemonResult!

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }
    
    func trimNewLines(text: String) -> String {
        print("trimlines")
        print(text)
        print(text.replacingOccurrences(of: "\n", with: " ").replacingOccurrences(of: "\\f", with: " "))
        print("--trimlines")
        return text.replacingOccurrences(of: "\n", with: " ")
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        pokemonDescription.text = ""
        type1Label.text = ""
        type2Label.text = ""

        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }
            do {
                self.result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    //set labels
                    self.navigationItem.title = self.capitalize(text: self.result.name)
                    self.nameLabel.text = self.capitalize(text: self.result.name)
                    self.numberLabel.text = String(format: "#%03d", self.result.id)
                    
                    //set image
                    let imageURL = URL(string: self.result.sprites.front_default!)!
                    do{
                        self.image.image = UIImage(data: try Data(contentsOf: imageURL))
                    }
                    catch let error {
                        print(error)
                    }

                    //set types
                    for typeEntry in self.result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                    
                    //set description
                    let descriptionURL = "https://pokeapi.co/api/v2/pokemon-species/\(self.result.id)"
                    URLSession.shared.dataTask(with: URL(string: descriptionURL)!) { (data, response, error) in
                        print("loaded description from api")
                        guard let data = data else {
                            return
                        }
                        
                        do {
                            let result = try JSONDecoder().decode(PokemonFlavorTextEntries.self, from: data)
                            print("worked")
                            DispatchQueue.main.async {
                                for flavor_text in result.flavor_text_entries{
                                    if flavor_text.language.name == "en"{
                                        print("yo")
                                        self.pokemonDescription.text = self.trimNewLines(text: flavor_text.flavor_text)
                                        print(self.trimNewLines(text: flavor_text.flavor_text))
                                        break
                                    }
                                }
                            }
                        }
                        catch let error {
                            print(error)
                        }
                    }.resume()
                    
                    let key = self.result.name + ".isCaught"
                    self.isCaught = UserDefaults.standard.bool(forKey: key)
                    
                    let title = self.isCaught ? "Release": "Catch"
                    self.catchButton.setTitle(title, for: .normal)
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    @IBAction func toggleCatch(){
        isCaught = !isCaught
        let title = isCaught ? "Release": "Catch"
        catchButton.setTitle(title, for: .normal)
        
        let key = self.result.name + ".isCaught"
        UserDefaults.standard.set(isCaught, forKey: key)
    }
}
