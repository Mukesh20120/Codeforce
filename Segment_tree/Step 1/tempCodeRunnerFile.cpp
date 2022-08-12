
        int q;
        cin >> q;
        while (q--){
            int l, r;
            cin >> l >> r;
            cout << seg1.query(0, 0, 4 * n, l, r) << endl;
        }
