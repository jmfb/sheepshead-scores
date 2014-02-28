$.ajax({ url: '/sheepshead.cgi?action=submit-hands', type: "POST", contentType: "application/json; charset=UTF-8", data: JSON.stringify({ playerNames: ["Jacob Buysse", "Ben Dixon", "Greg Smith", "Ezra McNichols", "Anne Sechtig", "Tracy Mueller" ], hands: [ { playerIndices: [0, 1, 2, 3, 4 ], doubler: true, handType: "normal", leadPlayerIndex: 0, score: { win: true, scoreTier: "noTricker", pickerPlayerIndex: 0, partnerPlayerIndex: 0 }}, { playerIndices: [1, 2, 3, 4, 5], doubler: false, handType: "leaster", leadPlayerIndex: 1, score: { primaryPlayerIndex: 2, secondaryPlayerIndex: 1 } }, { playerIndices: [2, 3, 4, 5, 0], doubler: false, handType: "misplay", leadPlayerIndex: 2, score: { loserPlayerIndex: 3 }} ]}), dataType: "json" })


$.ajax({ url: '/sheepshead.cgi?action=submit-hands', type: "POST", contentType: "application/json; charset=UTF-8", data: JSON.stringify({ playerNames: ["Jacob Buysse", "Ben Dixon", "Greg Smith", "Ezra McNichols", "Anne Sechtig"], hands: [ { playerIndices: [0, 1, 2, 3, 4 ], doubler: false, handType: "leaster", leadPlayerIndex: 0, score: { primaryPlayerIndex: 0, secondaryPlayerIndex: null }}]}), dataType: "json" })

